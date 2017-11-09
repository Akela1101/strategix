/* 
 * File:   TerrainPositioner.cpp
 * Author: Akela1101
 * 
 * Created on 4 Апрель 2010 г., 13:53
 */

#include <fstream>

#include "TerrainPositioner.h"


namespace Sample1
{
	using namespace Ogre;
	using namespace std;

TerrainPositioner::TerrainPositioner(const char fileName[])
{
	// Зачем названия текстур читать ?!
	ifstream fin(fileName);
	char cString[100];
	fin.getline(cString, 100);
	name = "Terrains"; // !!!!!! Name of material, not the texture file
	fin >> divs;

	float retard;
	string terrName;
	for( int pos = 0; ; ++pos )
	{
		fin >> retard >> terrName;
		if( !fin.good() )
			break;

		positions[terrName] = pos;
	}
	fin.close();
}

const FloatRect TerrainPositioner::GetTexRect(string terrName)
{
	// Getting position from name
	const short terr_pos = positions[terrName];
	const short x = terr_pos % divs;
	const short y = terr_pos / divs;
	const float length = 1.0 / divs;

	FloatRect rc(x * length, y * length, (x + 1) * length, (y + 1) * length);

	return rc;
}

}
