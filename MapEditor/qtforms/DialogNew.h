/* 
 * File:   DialogNew.h
 * Author: akela
 *
 * Created on 8 Сентябрь 2010 г., 0:10
 */

#ifndef _DIALOGNEW_H
#define	_DIALOGNEW_H

#include "ui_DialogNew.h"


class DialogNew : public QDialog
{
	Q_OBJECT
	friend class MainForm;

private:
	QString mapName;
	int mapWidth, mapHeight;

private slots:
	void accept();

public:
	DialogNew();
	virtual ~DialogNew();
private:
	Ui::DialogNew widget;
};

#endif	/* _DIALOGNEW_H */
