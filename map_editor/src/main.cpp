#include <forms/MainForm.h>
#include <QApplication>

#ifdef Q_OS_WIN
	Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

int main(int argc, char* argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);
	
	QApplication app(argc, argv);
	
	MainForm mainForm;
	mainForm.show();
	
	return app.exec();
}
