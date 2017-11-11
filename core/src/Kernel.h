#ifndef _KERNEL_H
#define    _KERNEL_H

#include "Strategix_Forward.h"

#include <vector>


/**
 * Main functionality is here.
 */
namespace Strategix::Kernel
{
using namespace std;

MapFull& GetMap();
vector<u_p<Player>>& GetPlayers();
ResourceInfo* GetResourceInfo(const string& name);
s_p<TechTree> MakeTechTreeCopy(const string& raceName);

// keep this calling order
void Configure(s_p<ConfigurationBuilder> configurationBuilder, s_p<TechTreesBuilder> techTreesBuilder);
void Init(const string& mapName);
void AddPlayer(u_p<Player> player);

void Start();
void Tick(float seconds);

vector<string> GetMapNames();
vector<string> GetRaceNames();
u_p<Resource> MakeResource(const string& name, float amount);
u_p<Resources> MakeResources(); // filled with zero
}

#endif    /* _KERNEL_H */

