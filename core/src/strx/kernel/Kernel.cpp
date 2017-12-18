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
#include <strx/player/Player.h>

#include "Kernel.h"
#include "Game.h"


namespace strx
{
namespace fs = boost::filesystem;
using PlayersType = umap<string, u_p<Player>>;
using st_timer = boost::asio::steady_timer;
using st_clock = chrono::steady_clock;

// Constants
static const auto minTick = 42ms;

// Variables
static s_p<Game> game;                        // main event receiver
static ConfigManager configManager;           // game configuration manager
static u_p<MapManager> mapManager;            // has all information about the map
static u_p<thread> kernelThread;              // main Kernel thread
nya::event_loop Kernel::eventLoop;            // asio::io_service event loop
//static u_p<nya::event_loop::work> dummyWork;  // work for io_service
static u_p<st_timer> timer;

static PlayersType players;                   // players by name
static ResourceInfosType resourceInfos;       // resource descriptions
static TechTreesType techTrees;               // technology trees


void Kernel::Configure(const string& configPath, const string& mapsDirectory)
{
	tie(resourceInfos, techTrees) = configManager.ParseConfig(configPath);
	mapManager = make_u<MapManager>(mapsDirectory);
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
	players.emplace(player->GetName(), player);
	game->PlayerAdded(player);
	
	player->Start();
}

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

void Kernel::Start(s_p<Game> game)
{
	strx::game = game;
	game->Start();
	
	timer.reset(new st_timer(eventLoop));
	timer->async_wait(TimerHandler);
	
	kernelThread.reset(new thread([]
	{
		nya::SetThreadName("strategix");
		try
		{
			eventLoop.run();
		}
		catch (exception& e)
		{
			error_log << "Unexpected error in strategix: " << e.what();
			// @#~ should call game to stop
		}
	}));
}

void Kernel::Stop()
{
	timer.reset();
	if (kernelThread) kernelThread->join();
	
	game.reset();
}

void Kernel::Tick(float seconds)
{
	try
	{
		for (auto& name_player : players)
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

bool Kernel::CheckResource(const string& name)
{
	return find(all_(resourceInfos), name) != resourceInfos.end();
}

const TechTree& Kernel::GetTechTree(const string& raceName)
{
	return *techTrees[raceName];
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
	for (auto&& name_tree : techTrees)
	{
		raceNames.push_back(name_tree.second->GetRaceName());
	}
	return raceNames;
}

const ResourceInfosType& Kernel::GetResourceInfos()
{
	return resourceInfos;
}

u_p<Resources> Kernel::MakeResources()
{
	auto resources = make_u<Resources>();
	for (auto&& resourceName : resourceInfos)
	{
		*resources += Resource(resourceName, 0);
	}
	return resources;
}

}