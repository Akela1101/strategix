#include <QApplication>
#include <logic/SampleUser.hpp>

INITIALIZE_EASYLOGGINGPP


int main(int argc, char* argv[])
try
{
	QApplication app(argc, argv);
	nya::init_logs("config/log.conf");

	sample1::SampleUser user;

	return app.exec();
}
catch (std::exception& e)
{
	error_log << "Error occurred:\n[" << e.what() << "] \nFinishing the game..." << std::endl;
	return EXIT_FAILURE;
}
catch (...)
{
	error_log << "Unexpected error occurred:\nFinishing the game..." << std::endl;
	return EXIT_FAILURE;
}
