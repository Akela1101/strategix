#include "ConfigurationBuilderFromXml.h"
#include "TechTreesBuilderFromXml.h"

#include "../../core/src/Strategix.h"
#include <boost/filesystem.hpp>
#include <iostream>


using namespace Strategix;
using namespace Sample1;
using namespace std;

#if defined( _MSC_VER )
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

int main(int argc, char* argv[])
{
	int ret;
#endif
	KernelBase::GS().Configure(s_p<ConfigurationBuilder>(new ConfigurationBuilderFromXml)
			, s_p<TechTreesBuilder>(new TechTreesBuilderFromXml));
	
	cout << endl << "Maps: " << endl;
	s_p<vector<string>> mapNames = KernelBase::GS().GetMapNames();
	for (auto&& mapName : *mapNames)
	{
		cout << mapName << endl;
	}
	
	cout << endl << "Race names: " << endl;
	s_p<vector<string>> raceNames = KernelBase::GS().GetRaceNames();
	for (auto&& raceName : *raceNames)
	{
		cout << raceName << endl;
	}
	
	// One Game
	{
		s_p<Kernel> kernel(new Kernel("1x1"));
		kernel->AddPlayer(s_p<Player>(new Player("Neko123", HUMAN, 0, "Spher")));
		kernel->AddPlayer(s_p<Player>(new Player("Inu456", AI, 1, "Spher")));
		
		try
		{
			// go
		}
		catch (Strategix::Exception& e)
		{
			// Already printed
		}
		catch (exception& e)
		{
			cout << endl << e.what() << endl;
		}
	}

#if defined( _MSC_VER )
	getch();
#endif
}