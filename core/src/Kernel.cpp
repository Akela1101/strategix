#include <Enti.h>
#include <MapFull.h>
#include <MapLocal.h>
#include <Player.h>
#include <ResourceInfo.h>
#include <Resources.h>
#include <ConfigurationManager.h>
#include <TechTreesBuilder.h>

#include <boost/filesystem.hpp>
#include <iostream>

#include "Kernel.h"
#include "KernelSlot.h"


namespace Strategix::Kernel
{
using namespace Strategix;
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

// Constants
static const umap<string, string> constants
		= {
				{ "config_file",      "config/strategix_config.xml" },
				{ "races_config_dir", "config/races/" },
				{ "terrains_file",    "maps/terrains.def" },
				{ "map_path_format",  "maps/%s.map" }
		};

// Variables
static s_p<KernelSlot> slot;            // Main event receiver
static u_p<MapFull> mapFull;            // Current map
static vector<u_p<Player>> players;     // List of players
static ResourceInfosType resourceInfos; // List of resource descriptoins
static TechTreesType techTrees;         // Technology trees


void Configure(s_p<KernelSlot>&& slot)
{
	Kernel::slot = slot;
	ConfigurationManager::ParseConfig(&resourceInfos);
	ConfigurationManager::ParseTechTrees(&techTrees);
}

void Init(const string& mapName)
{
	if (!slot) STRATEGIX_THROW("Configure() should be run before Init().");
	
	mapFull = make_u<MapFull>(mapName);
}

void AddPlayer(u_p<Player> player)
{
	if (!mapFull) STRATEGIX_THROW("Init() should be run before AddPlayer().");
	
	Player* pPlayer = player.get();
	player->Init(mapFull->CreateMapLocal(pPlayer));
	
	players.push_back(move(player));
	
	slot->OnAddPlayer(pPlayer);
}

void Tick(float seconds)
{
	for (auto& player : players)
	{
		player->Tick(seconds);
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

string Get(const string& name)
{
	try { return constants.at(name); }
	catch (...)
	{
		STRATEGIX_WARNING(name + " is not defined in Strategix::Kernel.");
		return "";
	}
}

MapFull& GetMap() { return *mapFull; }

vector<u_p<Player>>& GetPlayers() { return players; }

ResourceInfo* GetResourceInfo(const string& name)
{
	auto iRi = resourceInfos.find(name);
	return iRi != resourceInfos.end() ? &*iRi->second : nullptr;
}

u_p<TechTree> MakeTechTreeCopy(const string& raceName)
{
	return make_u<TechTree>(*techTrees[raceName]);
}

vector<string> GetMapNames()
{
	vector<string> mapNames;
	try
	{
		fs::recursive_directory_iterator it("maps/"), eod;
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
		STRATEGIX_ERROR(e.what());
	}
	return mapNames;
}

vector<string> GetRaceNames()
{
	vector<string> raceNames;
	for (auto&& name_tree : techTrees)
	{
		raceNames.push_back(name_tree.second->raceName);
	}
	return raceNames;
}

u_p<Resource> MakeResource(const string& name, float amount)
{
	auto iRi = resourceInfos.find(name);
	if (iRi == resourceInfos.end())
	{
		STRATEGIX_THROW("There is no resource named: " + name);
	}
	return make_u<Resource>(iRi->first, amount);
}

u_p<Resources> MakeResources()
{
	auto resources = make_u<Resources>();
	for (auto&& name_resource : resourceInfos)
	{
		*resources += Resource(name_resource.first, 0);
	}
	return resources;
}

}