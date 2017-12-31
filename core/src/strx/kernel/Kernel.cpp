#include <future>
#include <thread>
#include <boost/asio/steady_timer.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/adaptors.hpp>
#include <nya/signal.hpp>

#include <strx/common/Resources.h>
#include <strx/common/TechTree.h>
#include <strx/entity/Entity.h>
#include <strx/common/EntityInfo.h>
#include <strx/game/Game.h>
#include <strx/kernel/ConfigManager.h>
#include <strx/kernel/MapManager.h>
#include <strx/map/Map.h>
#include <strx/network/Message.h>
#include <strx/network/Server.h>
#include <strx/player/Player.h>

#include "Kernel.h"


namespace strx
{
namespace fs = boost::filesystem;
using st_timer = boost::asio::steady_timer;
using st_clock = chrono::steady_clock;

// Constants
static const auto minTick = 42ms;

// Variables
static umap<int, u_p<GameMessage>> games;     // list of games
static s_p<Game> game;                        // single game
static ConfigManager configManager;           // game configuration manager
static u_p<MapManager> mapManager;            // has all information about the map
static u_p<thread> kernelThread;              // main kernel thread
static u_p<st_timer> timer;                   // tick timer


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

		for (auto& player : game->GetPlayers() | nya::map_values)
		{
			player->Tick(seconds);
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

void Kernel::OnReceiveMessage(s_p<Message> message, NetId netId)
{
	switch (message->GetType())
	{
	case Message::Type::CONTEXT: ContextRequested(netId); break;
	case Message::Type::PLAYER: AddPlayer(sp_cast<PlayerMessage>(message), netId); break;
	case Message::Type::START: StartGame(netId); break;
	default:
		const char* t = message->GetType().c_str();
		nya_throw << "Unable to handle message with type: " << (t[0] == '!' ? message->GetType() : t);
	}
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

void Kernel::Init(const string& configPath)
{
	configManager.ParseConfig(configPath);
	mapManager = make_u<MapManager>(configManager.GetMapsPath());

	// @#~
	AddGame("small", "root");

	Server::Run(configManager.GetServerPort());

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

void Kernel::ContextRequested(NetId clientId)
{
	auto contextMessage = make_s<ContextMessage>(configManager.GetResourceInfos());
	Server::SendMessageOne(contextMessage, clientId);

	auto gamesMessage = make_s<MessageVector>();
	for (const auto& gameMessage : games | nya::map_values)
	{
		gamesMessage->push_back(make_u<GameMessage>(*gameMessage));
	}
	Server::SendMessageOne(gamesMessage, clientId);
}

void Kernel::LoadMap(const string& mapName)
{
	if (!mapManager) nya_throw << "Init() should be run before LoadMap().";

	mapManager->LoadMap(mapName);
}


void Kernel::AddGame(const string& mapName, const string& creatorName)
{
	game.reset(new Game());

	auto gameMessage = make_u<GameMessage>();
	gameMessage->id = 1;
	gameMessage->started = false;
	gameMessage->mapName = mapName;
	gameMessage->creatorName = creatorName;
	games.emplace(1, move(gameMessage));

	LoadMap(mapName);
}

void Kernel::AddPlayer(s_p<PlayerMessage> playerMessage, NetId netId)
{
	game->AddPlayer(playerMessage, netId);
	Server::SendMessageAll(playerMessage);
}

void Kernel::StartGame(NetId clientId)
{
	//TODO: check all clients are ready
	game->Start(*mapManager);
}

}
