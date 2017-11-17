#ifndef _KERNEL_H
#define    _KERNEL_H

#include <Strategix_Forward.h>
#include <vector>


/**
 * Main functionality is here.
 */
namespace strategix::Kernel
{
using namespace std;

// keep this calling order
void Configure(KernelSlot* slot);
void SetMap(const string& mapName);
void AddPlayer(PlayerSlot* playerSlot);

void Start();
void Tick(float seconds);
void PrintInfo();

const string& GetMapsDir();
MapFull& GetMap();
bool CheckResource(const string& name);
const TechTree& GetTechTree(const string& raceName);
vector<string> GetMapNames();
vector<string> GetRaceNames();
u_p<Resource> MakeResource(const string& name, float amount);
u_p<Resources> MakeResources(); // filled with zero
}

#endif    /* _KERNEL_H */

