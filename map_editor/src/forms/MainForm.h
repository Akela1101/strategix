#ifndef _MAINFORM_H
#define    _MAINFORM_H

#include <Common.h>
#include <ui_MainForm.h>


class MainForm : public QMainWindow
{
Q_OBJECT
	
	Ui::MainForm widget;
	
	bool isMapOpened, isMapSaved;
	QString fileName;
	const QListWidgetItem* currentItem;

public:
	MainForm();
	
	const QListWidgetItem* GetCurrentWidgetItem() const { return currentItem; }
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
	std::pair<std::string, int> LoadTerrainDescription();
	void ListWidgetFillTerrains(const std::string& terrainsImageFileName, int divs);
	void ListWidgetFill(ToolType type, const std::string& name, const QString& imageFileName, QListWidget* listWidget);
	void ListWidgetFill(ToolType type, const std::string& name, const QPixmap& pixmap, QListWidget* listWidget);
	bool TrySaveMap();
	QString SaveMap();
};

#endif    /* _MAINFORM_H */
