#ifndef _DIALOGNEW_H
#define    _DIALOGNEW_H

#include "ui_DialogNew.h"


class DialogNew : public QDialog
{
Q_OBJECT
	
	friend class MainForm;
	
	Ui::DialogNew widget;
	
	QString mapName;
	size_t mapWidth, mapHeight;

public:
	DialogNew();
	virtual ~DialogNew();

private slots:
	void accept();
};

#endif    /* _DIALOGNEW_H */
