#include "Enti.h"
#include "MapFull.h"
#include "Player.h"
#include "Resources.h"
#include "ConfigurationBuilder.h"
#include "TechTreesBuilder.h"

#include <boost/filesystem.hpp>

#include "Kernel.h"


namespace Strategix::Kernel
{
using namespace Strategix;
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

static u_p<MapFull> mapFull;
static vector<u_p<Player>> players;
static ResourceInfosType resourceInfos;
static TechTreesType techTrees;


MapFull& GetMap() { return *mapFull; }

vector<u_p<Player>>& GetPlayers() { return players; }

ResourceInfo* GetResourceInfo(const string& name)
{
	auto iRi = resourceInfos.find(name);
	return iRi != resourceInfos.end() ? &*iRi->second : nullptr;
}

s_p<TechTree> MakeTechTreeCopy(const string& raceName) { return make_s<TechTree>(*techTrees[raceName]); }


void Configure(s_p<ConfigurationBuilder> configurationBuilder, s_p<TechTreesBuilder> techTreesBuilder)
{
	configurationBuilder->Build(&resourceInfos);
	techTreesBuilder->Build(&techTrees);
}

void Init(const string& mapName)
{
	mapFull = make_u<MapFull>(mapName);
}

void AddPlayer(u_p<Player> player)
{
	player->mapLocal = mapFull->CreateMapLocal(player.get());
	players.push_back(move(player));
}

void Start()
{
	// @#~ Check for kernel consistence, run initial functions
	
	// Players' initialization
	for (auto& player : players)
	{
		player->Start();
	}
	
	// @#~
	players[0]->AddEnti(make_s<Enti>(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(4, 6)));
	players[0]->AddEnti(make_s<Enti>(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 7)));
	players[0]->AddEnti(make_s<Enti>(&*players[0]->techTree->Node("Spher_Worker"), MapCoord(6, 6)));
	
	// @#~
	players[0]->AddResource(*MakeResource("gold", 0)); // badly refreshing
}

void Tick(const float seconds)
{
	for (auto& player : players)
	{
		player->Tick(seconds);
	}
}

vector<string> GetMapNames()
{
	vector<string> mapNames;
	fs::recursive_directory_iterator it("maps/"), eod;
	for (; it != eod; ++it)
	{
		const fs::path& p = *it;
		if (fs::is_regular_file(p) && fs::extension(p) == ".map")
		{
			mapNames.push_back(p.stem().string());
		}
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
		STRATEGIX_EXCEPTION("There is no resource named: " + name);
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