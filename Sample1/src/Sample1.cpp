/* 
 * File:   Sample1.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 0:15
 */

#include "Nya.hpp"
#include "Kernel.h"
#include "OgreWrap.h"

#include <boost/filesystem.hpp>

using namespace Strategix;
using namespace Sample1;
using namespace std;

#if defined( __WIN32__ ) || defined( _WIN32 )
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	//SetCurrentDirectory("C:\\.......");
#else

#include "stdlib.h"
int main(int argc, char *argv[])
{
	//int ret = chdir("NetBeansProjects/Strategix/Sample1");
#endif
	// Also change plugin folder respectively

	// What is current path? Must be as in chdir.
	cout << "Current dir: " << boost::filesystem::current_path() << endl;

	//
	cout << endl << "Mapss: " << endl;
	sh_p<std::vector<std::string> > mapNames = Kernel::GS().GetMapNames();
	foreach(std::string mapName, *mapNames)
	{
		cout << mapName << endl;
	}

	//
	cout << endl << "Race names: " << endl;
	sh_p<std::vector<std::string> > raceNames = Kernel::GS().GetRaceNames();
	foreach(std::string raceName, *raceNames)
	{
		cout << raceName << endl;
	}

	//cout << endl << Kernel::GS().techTrees["Spher"]->techMap["Spher_Worker"]->file << endl;

	// One Game
	{
		std::vector<sh_p<Player> > players;
		players.push_back(sh_p<Player>(new Player("Neko", HUMAN, 0, "Spher")));

		//cout << endl << players[0].get()->techTree->techMap["Spher_Worker"]->file << endl << endl;

		Game::GS().Start("1x1", players);

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
		catch( std::exception &e )
		{
			cerr << "Exception: " << e.what() << endl;
		}
		cout << endl << "@@@@@@@@@@@@@@@@@" << endl;
	}

	// Reenable autorepeat in KDE ! *WALL*
#if !defined( __WIN32__ ) && !defined( _WIN32 )
	cout << endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	std::system("xset r");
#endif

	return 0;
}