#include <future>
#include <thread>
#include <boost/filesystem.hpp>
#include <nya/signal.hpp>

#include <strx/common/Resources.h>
#include <strx/common/TechTree.h>
#include <strx/entity/Enti.h>
#include <strx/entity/EntiInfo.h>
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


// Variables
static Game* game = nullptr;                  // main event receiver
static ConfigManager configManager;           // game configuration manager
static u_p<MapManager> mapManager;            // has all information about the map
static u_p<thread> kernelThread;              // main Kernel thread
nya::event_loop Kernel::eventLoop;            // asio::io_service event loop
static u_p<nya::event_loop::work> dummyWork;  // work for io_service

static PlayersType players;                   // players by name
static Player* humanPlayer = nullptr;         // human player
static ResourceInfosType resourceInfos;       // resource descriptions
static TechTreesType techTrees;               // technology trees


void Kernel::Configure(const string& configPath, const string& mapsDirectory)
{
	tie(resourceInfos, techTrees) = configManager.ParseConfig(configPath);
	mapManager = make_u<MapManager>(mapsDirectory);
}

void Kernel::LoadMap(const string& mapName)
{
	if (!mapManager)
		nya_throw << "Configure() should be run before LoadMap().";
	
	mapManager->LoadMap(mapName);
}

void Kernel::AddPlayer(PlayerSlot* playerSlot)
{
	if (!mapManager) nya_throw << "LoadMap() should be run before AddPlayer().";
	
	auto player = new Player(playerSlot);
	players.emplace(player->GetName(), player);
	
	player->Init(mapManager->CreateMap(*player));
	
	if (playerSlot->GetType() == PlayerType::HUMAN)
	{
		humanPlayer = player;
	}
}

void Kernel::Start()
{
	dummyWork.reset(new nya::event_loop::work(eventLoop));
	kernelThread.reset(new thread([]
	{
		nya::SetThreadName("strategix");
		eventLoop.run();
	}));
}

void Kernel::Stop()
{
	dummyWork.reset();
	if (kernelThread) kernelThread->join();
}

void Kernel::Tick(float seconds)
{
	for (auto& name_player : players)
	{
		name_player.second->Tick(seconds);
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

Player& Kernel::GetHumanPlayer()
{
	if (humanPlayer) return *humanPlayer;
	
	nya_throw << "Human player wasn't created.";
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

u_p<Resource> Kernel::MakeResource(const string& name, ResourceUnit amount)
{
	if (!CheckResource(name))
	{
		nya_throw << "There is no resource named: " << name;
	}
	return make_u<Resource>(name, amount);
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