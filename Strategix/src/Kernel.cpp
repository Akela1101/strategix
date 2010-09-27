/* 
 * File:   Kernel.cpp
 * Author: Akela1101
 * 
 * Created on 13 Февраль 2010 г., 23:19
 */

#include "Kernel.h"
#include "TechTreeBuilderFromXml.h"

using namespace std;
using namespace boost;
using namespace Strategix;

Kernel::Kernel()
{
}

Kernel::~Kernel()
{
}

void Kernel::InitGame(string mapName, vector<PlayerInitial> playerInitials)
{
	// Load Tech Tree	
	string raceName = "Neko";
	shared_ptr<TechTree> shpTechTree(new TechTree(raceName));

	TechTreeBuilderFromXml ttBuilder;
	shpTechTree->Build(ttBuilder);

	techTrees.insert(pair<string, shared_ptr<TechTree> >(raceName, shpTechTree));

	cout << techTrees["Neko"]->techMap["Worker"]->name;
	
	// Load Map
	Map::GS().InitFromTextFile(mapName);
	//Map::GS().OutMatrix();
}
