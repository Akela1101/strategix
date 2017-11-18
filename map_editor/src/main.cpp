#include <forms/MainForm.h>
#include <exception>
#include <QApplication>
#include <QMessageBox>


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

int main(int argc, char* argv[])
{
	InitLogs();
	
	QApplication app(argc, argv);
	try
	{
		MainForm mainForm;
		mainForm.show();
		return app.exec();
	}
	catch (std::exception& e)
	{
		QMessageBox::warning(nullptr, "Warning!", QString::fromUtf8(e.what()), QMessageBox::Cancel);
	}
}
