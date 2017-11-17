#ifndef _DIALOGNEW_H
#define    _DIALOGNEW_H

#include "ui_DialogNew.h"


class DialogNew : public QDialog
{
Q_OBJECT
	
	friend class MainForm;

private:
	QString mapName;
	size_t mapWidth, mapHeight;

private slots:
	void accept();

public:
	DialogNew();
	virtual ~DialogNew();
private:
	Ui::DialogNew widget;
};

#endif    /* _DIALOGNEW_H */
