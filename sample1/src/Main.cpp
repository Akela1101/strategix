#include <QApplication>
#include <slots/SampleGame.h>


INITIALIZE_EASYLOGGINGPP


int main(int argc, char* argv[])
{
	using namespace sample1;

	QApplication app(argc, argv);
	nya::init_logs("config/log.conf");

	SampleGame::Configure();

	try  // run a game
	{
		// connect to server asynchronously
		SampleGame game(argc == 1 ? 1 : 3);  //TODO: select player in gui

		// start graphics
		return app.exec();
	}
	catch (nya::exception& e)
	{
		error_log << "Strategix error occurred:\n[" << e.what() << "] \nFinishing the game..." << endl;
		return 1;
	}
	catch (exception& e)
	{
		error_log << "Unexpected error occurred:\n[" << e.what() << "] \nFinishing the game..." << endl;
		return 2;
	}
}
