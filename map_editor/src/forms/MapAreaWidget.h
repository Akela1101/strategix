#ifndef _MAPAREA_H
#define    _MAPAREA_H

#include <QScrollArea>
#include <nya.hpp>


class MainForm;
class MapInfo;
class MapAreaWidgetImpl;
class QListWidgetItem;

class MapAreaWidget : public QScrollArea
{
	MapAreaWidgetImpl* impl;

public:
	MapAreaWidget(QWidget* parent = nullptr);
	~MapAreaWidget() override;
	
	void SetInfoFromItem(const QListWidgetItem* item, ToolInfo* info);
	const QString& GetMapName() const;
	void AssignMainForm(MainForm* mainForm);
	void SetMap(const QString& name, size_t width, size_t height);
	void LoadFromFile(const QString& fileName);
	bool SaveToFile(const QString& fileName) const;

protected:
	void wheelEvent(QWheelEvent* event);
};
#endif    /* _MAPAREA_H */

