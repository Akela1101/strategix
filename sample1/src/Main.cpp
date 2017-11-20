#include <SampleEntiSlot.h>
#include <SampleKernelSlot.h>
#include <SamplePlayerSlot.h>
#include <Strategix.h>


INITIALIZE_EASYLOGGINGPP


using namespace strx;
using namespace sample1;
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


void InitLogs()
{
	el::Loggers::configureFromGlobal("config/log.conf");
	el::Configurations conf;
	conf.parseFromText("*GLOBAL:\n FORMAT = %msg", el::Loggers::getLogger("default")->configurations());
	el::Loggers::getLogger("raw")->configure(conf);
}

int main(int argc, char* argv[])
{
#endif
	InitLogs();
	
	// initialize graphics and make slot to it
	Kernel::Configure(new SampleKernelSlot("config/strategix.json", "maps"));

	Kernel::PrintInfo();

	try // run a game
	{
		// initialize map and players
		Kernel::LoadMap("1x1");
		
		auto inu = new SamplePlayerSlot("Inu", HUMAN, 0, "Spher");
		inu->AddEnti(new SampleEntiSlot("Spher_Worker"));
		
		auto saru = new SamplePlayerSlot("Saru", AI, 1, "Spher");
		saru->AddEnti(new SampleEntiSlot("Spher_Worker"));
		
		Kernel::AddPlayer(inu);
		Kernel::AddPlayer(saru);
		
		// start event loop in other thread
		Kernel::Start();
	}
	catch (nya::exception& e)
	{
		fatal_log << "Strategix error occurred. \nTerminating..." << endl;
	}
	catch (exception& e)
	{
		fatal_log << "Unexpected error occurred [" << e.what() << "] \nTerminating..." << endl;
	}

#if defined( _MSC_VER )
	getch();
#endif
}