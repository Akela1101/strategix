#ifndef _KERNEL_H
#define    _KERNEL_H

#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class Kernel
{
public:
	s_p<MapFull> mapFull;
	vector<s_p<Player>> players; // @#~ map better...

public:
	Kernel(const string& mapName);
	void AddPlayer(s_p<Player> player);
	
	void Start();
	void Tick(float seconds);
	
	inline MapFull& GetMap()
	{ return *mapFull; }
};
}

#endif    /* _KERNEL_H */

