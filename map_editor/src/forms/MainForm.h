#ifndef _MAINFORM_H
#define    _MAINFORM_H

#include <nya.hpp>
#include <MapInfo.h>

#include <ui_MainForm.h>


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
	
	QString terrainsImageFileName;
	int divs;
	QList<TerrainInfo> terrainInfos;

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
	void LoadTerrainDescription();
	bool TrySaveMap();
	QString SaveMap();
	QString GetMapsPath() const;
	void AddToListWidget(int objId, QString name, QPixmap pixmap
			, QHash<int, s_p<ObjectInfo>>* pInfos, QListWidget* listWidget);
	
};

extern const char mapFileTopString[];

#endif    /* _MAINFORM_H */
