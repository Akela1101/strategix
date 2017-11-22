#ifndef _MAINFORM_H
#define _MAINFORM_H

#include <MapInfo.h>
#include <ui_MainForm.h>

namespace map_editor
{
using namespace map_info;

class MainForm : public QMainWindow
{
Q_OBJECT
	
	Ui::MainForm widget;
	
	bool isMapOpened, isMapSaved;
	QString fileName;
	umap<const QListWidgetItem*, ToolInfo*> infoFromItem;

public:
	MainForm();

public slots:
	void MapChanged(bool yes = true);

private slots:
	void FileNew();
	void FileSave();
	void FileLoad();
	void FileExit();
	void HelpAbout();
	
	void CurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
	void CurrentToolboxItemChanged(int index);

private:
	void ListWidgetFill(ToolType type, const std::string& name, QListWidget* listWidget);
	bool TrySaveMap();
	QString SaveMap();

signals:
	void CurrentToolChanged(ToolInfo* tool);
};

}

#endif    /* _MAINFORM_H */
