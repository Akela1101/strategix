#ifndef _MAPFULL_H
#define    _MAPFULL_H

#include "Map.h"

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#include "Strategix_Forward.h"


namespace strategix
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
		Terrain(string name, float retard) : name(std::move(name)), retard(retard) {}
	};

protected:
	umap<int, Terrain> terrains;
	int nPlayers;
	vector<MapCoord> initialPositions;
	
public:
	MapFull(const string& name);
	MapFull(const MapFull& _c) = delete;
	MapFull& operator=(const MapFull& _c) = delete;
	
	const Terrain& GetTerrain(int terrainType) const { return terrains.find(terrainType)->second; }
	MapCoord GetInitialPostion(int iPlayer) const { return initialPositions[iPlayer]; }
	
	u_p<MapLocal> CreateMapLocal(Player* player);
	
	float PickResource(Mine* mine, float amount) override;
	
private:
	string GetFilePath(const string& name) const;
};
}

#endif    /* _MAPFULL_H */

