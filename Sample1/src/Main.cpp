/* 
 * File:   Main.cpp
 * Author: Akela1101
 * 
 * Created on 14 Февраль 2010 г., 0:15
 */

#include "MyApp.h"

#include "Player.h"
#include "Kernel.h"
#include "KernelBase.h"
#include "TechTreesBuilderFromXml.h"

#include <OgreException.h>

#include <boost/filesystem.hpp>

#include "Nya.hpp"


using namespace Strategix;
using namespace Sample1;
using namespace std;

#if defined( __WIN32__ ) || defined( _WIN32 )
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

static const WORD MAX_CONSOLE_LINES = 1000;

void RedirectIOToConsole()
{
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );

	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );

	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
	// point to console as well
	ios::sync_with_stdio();
}


INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	RedirectIOToConsole();
	//SetCurrentDirectory("C:\\.......");
#else

#include "stdlib.h"
int main(int argc, char *argv[])
{
	int ret;
	// ret = chdir("NetBeansProjects/Strategix/Sample1");
#endif
	// Also change plugin folder respectively

	// What is current path? ( Must be /Strategix/Sample1 )
	cout << "Current dir: " << boost::filesystem::current_path() << endl;

	KernelBase::GS().Configure("xml/strategix_config.xml");

	KernelBase::GS().BuildTechTrees(sh_p<TechTreesBuilder>(new TechTreesBuilderFromXml));

	//
	cout << endl << "Maps: " << endl;
	sh_p<std::vector<std::string> > mapNames = KernelBase::GS().GetMapNames();
	foreach(std::string mapName, *mapNames)
	{
		cout << mapName << endl;
	}

	//
	cout << endl << "Race names: " << endl;
	sh_p<std::vector<std::string> > raceNames = KernelBase::GS().GetRaceNames();
	foreach(std::string raceName, *raceNames)
	{
		cout << raceName << endl;
	}

	// One Game
	{
		sh_p<Kernel> kernel(new Kernel("1x1"));
		kernel->AddPlayer(sh_p<Player>(new Player("Neko123", HUMAN, 0, "Spher")));
		kernel->AddPlayer(sh_p<Player>(new Player("Inu456", AI, 1, "Spher")));

		// Graphics init.
		MyApp myApp(kernel);
		try
		{
			myApp.go(false);
		}
		catch( Ogre::Exception& e )
		{
			cout << endl << e.what() << endl;
		}
		catch( std::exception &e )
		{
			cout << endl << e.what() << endl;
		}
		cout << endl << "Exit from Ogre. Start to destruct it." << endl;
	}

// Reenable autorepeat in KDE ! *WALL*
#ifdef __linux__
	cout << endl << "Setting keyboard autorepeat back ON." << endl << endl;
	ret = std::system("xset r");
#endif

#if defined( __WIN32__ ) || defined( _WIN32 )
	getch();
#endif

	return 0;
}