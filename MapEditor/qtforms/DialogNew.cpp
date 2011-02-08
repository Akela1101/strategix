/*
 * File:   DialogNew.cpp
 * Author: akela
 *
 * Created on 8 Сентябрь 2010 г., 0:10
 */

#include "DialogNew.h"
#include <QtGui/qmessagebox.h>


DialogNew::DialogNew()
{
	widget.setupUi(this);
}

DialogNew::~DialogNew()
{
}

void DialogNew::accept()
{
	// Get name, size
	mapName = widget.lineEdit->text();
	if(	mapName == "" )
	{
		QMessageBox::information(this, tr("Warning!"), tr("<b>Give a name for the map!</b>"));
		return;
	}

	mapWidth = widget.horizontalSlider->sliderPosition();
	mapHeight = widget.verticalSlider->sliderPosition();
	
	QDialog::accept();
}
