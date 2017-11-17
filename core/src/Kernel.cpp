#include <ConfigurationManager.h>
#include <entity/Enti.h>
#include <entity/EntiInfo.h>
#include <map/MapFull.h>
#include <map/MapLocal.h>
#include <player/Player.h>
#include <Resources.h>
#include <TechTreesBuilder.h>

#include <boost/filesystem.hpp>

#include "Kernel.h"
#include "KernelSlot.h"


namespace strategix::Kernel
{
using namespace strategix;
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;


using PlayersType = umap<string, u_p<Player>>;


// Variables
static u_p<KernelSlot> slot;            // main event receiver
static u_p<MapFull> mapFull;            // current map
static PlayersType players;             // players by name
static ResourceInfosType resourceInfos; // resource descriptions
static TechTreesType techTrees;         // technology trees
static string mapsDirectory;            // usually "maps"

void Configure(KernelSlot* slot)
{
	Kernel::slot.reset(slot);
	tie(resourceInfos, techTrees) = ConfigurationManager().ParseConfig(slot->GetConfigPath());
	mapsDirectory = slot->GetMapsPath();
}

void SetMap(const string& mapName)
{
	if (!slot) throw_nya << "Configure() should be run before SetMap().";
	
	mapFull = make_u<MapFull>(mapName);
}

void AddPlayer(PlayerSlot* playerSlot)
{
	if (!mapFull) throw_nya << "SetMap() should be run before AddPlayer().";
	
	auto player = new Player(playerSlot);
	player->Init(mapFull->CreateMapLocal(player));
	
	players.emplace(player->GetName(), player);
}

void Start()
{}

void Tick(float seconds)
{
	for (auto& name_player : players)
	{
		name_player.second->Tick(seconds);
	}
}

void PrintInfo()
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

const string& GetMapsDir() { return mapsDirectory; }

MapFull& GetMap() { return *mapFull; }

bool CheckResource(const string& name)
{
	return find(all_(resourceInfos), name) != resourceInfos.end();
}

const TechTree& GetTechTree(const string& raceName)
{
	return *techTrees[raceName];
}

vector<string> GetMapNames()
{
	vector<string> mapNames;
	try
	{
		fs::recursive_directory_iterator it(mapsDirectory), eod;
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

vector<string> GetRaceNames()
{
	vector<string> raceNames;
	for (auto&& name_tree : techTrees)
	{
		raceNames.push_back(name_tree.second->GetRaceName());
	}
	return raceNames;
}

u_p<Resource> MakeResource(const string& name, float amount)
{
	if (!CheckResource(name))
	{
		throw_nya << "There is no resource named: " << name;
	}
	return make_u<Resource>(name, amount);
}

u_p<Resources> MakeResources()
{
	auto resources = make_u<Resources>();
	for (auto&& resourceName : resourceInfos)
	{
		*resources += Resource(resourceName, 0);
	}
	return resources;
}

}