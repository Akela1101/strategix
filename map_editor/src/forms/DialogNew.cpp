#include <QMessageBox>

#include "DialogNew.h"


DialogNew::DialogNew()
{
	widget.setupUi(this);
}

DialogNew::~DialogNew() = default;

void DialogNew::accept()
{
	// Get name, size
	mapName = widget.lineEdit->text();
	if (mapName == "")
	{
		QMessageBox::information(this, tr("Warning!"), tr("<b>Give a name for the map!</b>"));
		return;
	}
	
	mapWidth = (size_t) widget.horizontalSlider->sliderPosition();
	mapHeight = (size_t) widget.verticalSlider->sliderPosition();
	
	QDialog::accept();
}
