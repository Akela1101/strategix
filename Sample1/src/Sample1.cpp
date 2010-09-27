/* 
 * File:   Sample1.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 0:15
 */

#include "Kernel.h"
#include "OgreWrap.h"

using namespace Strategix;
using namespace Sample1;

#if defined( __WIN32__ ) || defined( _WIN32 )
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
#else

#include <unistd.h>

int main(int argc, char *argv[])
{	
	// If run directory fails to set !!!!!!!!!!!!!!!
	// Also change plugin folder respectively	
	int ret = chdir("NetBeansProjects/Strategix/Sample1");

	char buffer[301];
	getcwd(buffer, 300);
	cout << "Current dir: " << buffer << endl;
#endif

	// Load kernel
	Kernel kernel;

	// Get all map list from Kernel
	// std::vector<MapInfo> mapInfo = kernel.GetAllMapInfos();

	// Get all races from Kernel
	// std::vector<std::string> raceNames = kernel.GetAllRaceNames();

	// Choose map, playerType, position, race
	std::string mapName = "1x1";
	std::string mapPath = "Maps/"; mapPath += mapName + ".map";

	std::vector<PlayerInitial> playerInitials;
	PlayerInitial playerInitial = {HUMAN, 0, "Neko"};
	kernel.InitGame(mapPath, playerInitials);

	// Graphics init.
	OgreWrap ogre_wrap;
	try
	{
		ogre_wrap.go();
	}
	catch( Exception& e )
	{
		cerr << "Ogre exception: " << e.what() << endl;
	}

	return 0;
}