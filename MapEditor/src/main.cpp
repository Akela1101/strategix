/*
 * File:   main.cpp
 * Author: akela
 *
 * Created on 4 Сентябрь 2010 г., 19:17
 */

#include <QtGui/QApplication>
#include "MainForm.h"

int main(int argc, char *argv[])
{
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QApplication app(argc, argv);

	MainForm mainForm;
	mainForm.show();

	return app.exec();
}
