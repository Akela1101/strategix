#pragma once

#include "ui_DialogNew.h"


namespace map_editor
{
class MainForm;
}

class DialogNew : public QDialog
{
	Q_OBJECT

	friend class map_editor::MainForm;

	Ui::DialogNew widget;

	QString mapName;
	int mapWidth, mapHeight;

public:
	DialogNew();
	virtual ~DialogNew();

private slots:
	void accept();
};
