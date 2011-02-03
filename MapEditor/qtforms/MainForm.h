/* 
 * File:   MainForm.h
 * Author: akela
 *
 * Created on 4 Сентябрь 2010 г., 19:28
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "Nya.hpp"
#include "MapInfo.h"

#include "ui_MainForm.h"
#include <map>
#include <vector>


class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	const QListWidgetItem *currentItem;
	int currentToolboxIndex;

private:
	Ui::MainForm widget;

	bool isMapOpened, isMapSaved;
	QString fileName;	

public:
	MainForm();
	virtual ~MainForm();

	void MapChanged();

private slots:
	void FileNew();
	void FileSave();
	void FileLoad();
	void FileExit();
	void HelpAbout();

	void CurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
	void CurrentToolboxItemChanged(int index);

private:
	bool TrySaveMap();
	QString SaveMap();
	QString GetMapsPath() const;
	void AddToListWidget(const int objId, const QString name, const QPixmap pixmap,
		std::map<int, sh_p<ObjectInfo> > *pInfos, QListWidget *listWidget);

};

#endif	/* _MAINFORM_H */
