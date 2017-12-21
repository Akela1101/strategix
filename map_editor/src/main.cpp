#include <exception>
#include <QApplication>
#include <QMessageBox>

#include <forms/MainForm.h>

#if defined(Q_OS_WIN) && defined(QT_STATIC_LINK)
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#endif

INITIALIZE_EASYLOGGINGPP


int main(int argc, char* argv[])
{
	using namespace map_editor;
	
	nya::init_logs("config/log.conf");
	
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
