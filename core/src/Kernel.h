#ifndef _KERNEL_H
#define    _KERNEL_H

#include <Strategix_Forward.h>
#include <vector>


/**
 * Main functionality is here.
 */
namespace Strategix::Kernel
{
using namespace std;

// keep this calling order
void Configure(s_p<KernelSlot>&& slot);
void Init(const string& mapName);
void AddPlayer(u_p<Player> player);

void Tick(float seconds);
void PrintInfo();

string Get(const string& name);
MapFull& GetMap();
vector<u_p<Player>>& GetPlayers();
ResourceInfo* GetResourceInfo(const string& name);
u_p<TechTree> MakeTechTreeCopy(const string& raceName);
vector<string> GetMapNames();
vector<string> GetRaceNames();
u_p<Resource> MakeResource(const string& name, float amount);
u_p<Resources> MakeResources(); // filled with zero
}

#endif    /* _KERNEL_H */

