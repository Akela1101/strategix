/* 
 * File:   MapFull.h
 * Author: Akela1101
 *
 * Created on 24 Март 2011 г., 14:02
 */

#ifndef _MAPFULL_H
#define	_MAPFULL_H

#include "Map.h"

#include <vector>
#include <map>

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

			Terrain() {}
			Terrain(const Terrain &_c) : name(_c.name), retard(_c.retard) {}
			Terrain(const string &name, const float retard) : name(name), retard(retard) {}
		};
		typedef map<short, Terrain> TerrainsType; // terrType -> Terrain

	public:
		const Terrain &GetTerrain(const short terrType) const { return terrains.find(terrType)->second; }

		int nPlayers;
		vector<MapCoord> initialPositions;

	protected:
		
		TerrainsType terrains;

	public:
		MapFull(const string &name);
		virtual ~MapFull();

	private:
		MapFull(const MapFull &_c);
		MapFull& operator =(const MapFull &_c);
				
		bool LoadTerrains();
		const string GetFilePath(const string &name);
	};
}

#endif	/* _MAPFULL_H */

