#include <slots/SampleGame.h>
#include <Strategix.h>

#include <QtPlugin>
#include <QApplication>

#ifdef Q_OS_WIN
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif


INITIALIZE_EASYLOGGINGPP

void InitLogs()
{
	el::Loggers::configureFromGlobal("config/log.conf");
	el::Configurations conf;
	conf.parseFromText("*GLOBAL:\n FORMAT = %msg", el::Loggers::getLogger("default")->configurations());
	el::Loggers::getLogger("raw")->configure(conf);
}


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
#endif
	using namespace strx;
	using namespace sample1;
	
	QApplication app(argc, argv);
	InitLogs();
	
	Kernel::Configure("config/strategix.json", "maps");
	//Kernel::PrintInfo();

	try // run a game
	{
		auto game = make_u<SampleGame>();
		
		// start event loop in other thread
		Kernel::Start();
		
		// start graphics engine
		game->Start();
		app.exec();
	}
	catch (nya::exception& e)
	{
		error_log << "Strategix error occurred:\n[" << e.what() << "] \nFinishing the game..." << endl;
	}
	catch (exception& e)
	{
		error_log << "Unexpected error occurred:\n[" << e.what() << "] \nFinishing the game..." << endl;
	}
	Kernel::Stop();

#if defined( _MSC_VER )
	getch();
#endif
}