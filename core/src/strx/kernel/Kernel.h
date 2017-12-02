#ifndef _KERNEL_H
#define _KERNEL_H

#include <Strategix_Forward.h>
#include <nya/signal.hpp>

/**
 * Main functionality is here.
 */
namespace strx
{
class Kernel
{
	static nya::event_loop eventLoop;

public:
	// keep this calling order
	static void Configure(const string& configPath, const string& mapsDirectory);
	static void LoadMap(const string& mapName);
	static void AddPlayer(PlayerSlot* playerSlot);
	
	static void Start();
	static void Stop();
	static void Tick(float seconds);
	static void PrintInfo();
	
	static bool CheckResource(const string& name);
	static Player& GetHumanPlayer();
	static const TechTree& GetTechTree(const string& raceName);
	static vector <string> GetMapNames();
	static vector <string> GetRaceNames();
	static u_p<Resource> MakeResource(const string& name, ResourceUnit amount);
	static u_p<Resources> MakeResources(); // filled with zero
	
	template<typename ...Args, typename Slot>
	static void Connect(nya::sig<void(Args...)>& signalFunc, Slot&& slotFunc)
	{
		nya::connect_in(eventLoop, signalFunc, slotFunc);
	}
};
}

#endif //_KERNEL_H

