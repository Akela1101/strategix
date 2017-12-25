#include <future>
#include <thread>
#include <boost/filesystem.hpp>
#include <boost/asio/steady_timer.hpp>
#include <nya/signal.hpp>

#include <strx/common/Resources.h>
#include <strx/common/TechTree.h>
#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/kernel/ConfigManager.h>
#include <strx/kernel/MapManager.h>
#include <strx/map/Map.h>
#include <strx/network/Message.h>
#include <strx/network/Server.h>
#include <strx/player/Player.h>

#include "Kernel.h"
#include "Game.h"


namespace strx
{
namespace fs = boost::filesystem;
using st_timer = boost::asio::steady_timer;
using st_clock = chrono::steady_clock;

// Constants
static const auto minTick = 42ms;

// Variables
static s_p<Game> game;                        // single game
static ConfigManager configManager;           // game configuration manager
static u_p<MapManager> mapManager;            // has all information about the map
static u_p<thread> kernelThread;              // main kernel thread
static u_p<st_timer> timer;                   // tick timer

// Signals
static nya::sig<void(s_p<Message>, NetId)> DoSendMessage;


void TimerHandler(const boost::system::error_code& error)
{
	static st_clock::time_point lastTime = st_clock::now();
	if (!error)
	{
		if (timer) timer->expires_from_now(minTick);

		using namespace chrono;
		auto now = st_clock::now();
		auto dms = duration_cast<milliseconds>(now - lastTime);
		lastTime = now;

		Kernel::Tick((double)dms.count() / 1000);

		if (timer) timer->async_wait(TimerHandler);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Kernel::Run(const string& configPath)
{
	Init(configPath);
	RunImpl();
}

void Kernel::RunAsync(const string& configPath)
{
	Init(configPath);
	kernelThread.reset(new thread(RunImpl));
}

void Kernel::Init(const string& configPath)
{
	configManager.ParseConfig(configPath);
	mapManager = make_u<MapManager>(configManager.GetMapsPath());

	Server::Run(10101);
	Server::connect(DoSendMessage, Server::OnSendMessage);

	timer.reset(new st_timer(eventLoop));
	timer->async_wait(TimerHandler);
}

void Kernel::RunImpl()
{
	nya_thread_name("_strx_");
	try
	{
		eventLoop.run();
	}
	catch (exception& e)
	{
		error_log << "Unexpected error in strategix: " << e.what();
		// @#~ should call game to stop
	}
}

void Kernel::LoadMap(const string& mapName)
{
	if (!mapManager) nya_throw << "Configure() should be run before LoadMap().";

	mapManager->LoadMap(mapName);
}

void Kernel::AddPlayer(const string& name, PlayerType type, int playerId, const string& raceName)
{
	if (!mapManager->HasMap()) nya_throw << "LoadMap() should be run before AddPlayer().";

	Map& map = mapManager->CreateMap(playerId);
	auto player = new Player(name, type, playerId, raceName, map);
	game->AddPlayer(u_p<Player>(player));
	player->Start();
}

void Kernel::Start(s_p<Game> game)
{
}

void Kernel::Finish()
{
	Server::Finish();

	timer.reset();
	if (kernelThread) kernelThread->join();
}

void Kernel::Tick(float seconds)
{
	try
	{
		if (!game) return;

		for (auto& name_player : game->GetPlayers())
		{
			name_player.second->Tick(seconds);
		}
	}
	catch (exception& e)
	{
		error_log << "Error during tick: " << e.what();
	}
}

void Kernel::PrintInfo()
{
	cout << "\nMaps: " << endl;
	for (auto&& mapName : GetMapNames())
	{
		cout << mapName << endl;
	}

	cout << "\nRace names: " << endl;
	for (auto&& raceName : GetRaceNames())
	{
		cout << raceName << endl;
	}
}

void Kernel::OnReceiveMessage(s_p<Message> message, NetId clientId)
{
	s_p<Message> outMessage;
	switch (message->type)
	{
		case Message::Type::RQ_CONTEXT:
			outMessage = make_s<ContextMessage>(configManager.GetResourceInfos());
			break;
		default:
			const char* t = message->type.c_str();
			nya_throw << "Unable to handle message with type: " << (t[0] == '!' ? message->type : t);
	}
	DoSendMessage(outMessage, clientId);
}

bool Kernel::CheckResource(const string& name)
{
	auto&& resourceInfos = configManager.GetResourceInfos();
	return find(all_(*resourceInfos), name) != resourceInfos->end();
}

const TechTree& Kernel::GetTechTree(const string& raceName)
{
	try
	{
		return *configManager.GetTechTrees().at(raceName);
	}
	catch (out_of_range&)
	{
		nya_throw << "No race [%s] in the tech tree."s % raceName;
	}
}

vector<string> Kernel::GetMapNames()
{
	vector<string> mapNames;
	try
	{
		fs::recursive_directory_iterator it(mapManager->GetMapsDirectory()), eod;
		for (; it != eod; ++it)
		{
			const fs::path& p = *it;
			if (fs::is_regular_file(p) && fs::extension(p) == ".map")
			{
				mapNames.push_back(p.stem().string());
			}
		}
	}
	catch (fs::filesystem_error& e)
	{
		error_log << e.what();
	}
	return mapNames;
}

vector<string> Kernel::GetRaceNames()
{
	vector<string> raceNames;
	for (auto&& name_tree : configManager.GetTechTrees())
	{
		raceNames.push_back(name_tree.second->GetRaceName());
	}
	return raceNames;
}

const ResourceInfosType& Kernel::GetResourceInfos()
{
	return configManager.GetResourceInfos();
}

u_p<Resources> Kernel::MakeResources()
{
	auto resources = make_u<Resources>();
	for (auto&& resourceName : *GetResourceInfos())
	{
		*resources += Resource(resourceName, 0);
	}
	return resources;
}

}
