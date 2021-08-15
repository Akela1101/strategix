#pragma once

#include "ui_DialogNew.h"


namespace map_editor
{
class MapForm;
}

class DialogNew : public QDialog
{
	Q_OBJECT

	friend class map_editor::MapForm;

	Ui::DialogNew widget;

	QString mapName;
	int mapWidth, mapHeight;

public:
	DialogNew();
	virtual ~DialogNew();

private slots:
	void accept();
};
