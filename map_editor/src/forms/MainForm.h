#ifndef _MAINFORM_H
#define    _MAINFORM_H

#include <nya.hpp>
#include "MapInfo.h"

#include "ui_MainForm.h"
#include <map>
#include <vector>


class MainForm : public QMainWindow
{
Q_OBJECT

public:
	const QListWidgetItem* currentItem;
	int currentToolboxIndex;

private:
	Ui::MainForm widget;
	
	bool isMapOpened, isMapSaved;
	QString fileName;

public:
	MainForm();
	
	void MapChanged();

private slots:
	void FileNew();
	void FileSave();
	void FileLoad();
	void FileExit();
	void HelpAbout();
	
	void CurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
	void CurrentToolboxItemChanged(int index);

private:
	bool TrySaveMap();
	QString SaveMap();
	QString GetMapsPath() const;
	void AddToListWidget(int objId, QString name, QPixmap pixmap
			, std::map<int, s_p<ObjectInfo>>* pInfos, QListWidget* listWidget);
	
};

extern const char mapFileTopString[];
extern const char terrainsDefinitionFileName[];

#endif    /* _MAINFORM_H */
