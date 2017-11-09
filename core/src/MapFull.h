/* 
 * File:   MapFull.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 14:02
 */

#ifndef _MAPFULL_H
#define    _MAPFULL_H

#include "Map.h"

#include <vector>
#include <string>
#include <map>

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

class MapFull : public Map
{
protected:
	struct Terrain
	{
		string name;
		float retard;
		
		Terrain() = default;
		
		Terrain(const Terrain& _c) = default;
		
		Terrain(const string& name, const float retard) : name(name), retard(retard) {}
	};

protected:
	map<int, Terrain> terrains;
	int nPlayers;
	vector<MapCoord> initialPositions;
	
	vector<s_p<MapLocal>> mapLocals;

public:
	MapFull(const string& name);
	
	const Terrain& GetTerrain(const int terrainType) const { return terrains.find(terrainType)->second; }
	
	const MapCoord GetInitialPostion(int iPlayer) const { return initialPositions[iPlayer]; }
	
	s_p<MapLocal> CreateMapLocal(Player* player);
	
	float PickResource(s_p<MapResource> mapResource, float amount);

private:
	MapFull(const MapFull& _c);
	MapFull& operator=(const MapFull& _c);
	
	bool LoadTerrains();
	
	const string GetFilePath(const string& name) const { return "Maps/" + name + ".map"; }
};
}

#endif    /* _MAPFULL_H */

