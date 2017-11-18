#ifndef _MAPAREA_H
#define    _MAPAREA_H

#include <nya.hpp>
#include <QtGui>
#include <QWidget>
#include <QListWidgetItem>
#include <QScrollArea>


class MainForm;
class MapInfo;

class MapAreaWidget : public QWidget
{
Q_OBJECT
	
	MainForm* mainForm;
	QScrollArea* scrollArea;
	umap<const QListWidgetItem*, ToolInfo*> infoFromItem;
	
	u_p<MapInfo> mapInfo;
	int tileSize;
	u_p<QPixmap> groundPixmap;
	u_p<QPixmap> frontPixmap;
	QRect lastRc;
	bool isHighlight;

public:
	MapAreaWidget(QWidget* parent = nullptr);
	~MapAreaWidget();
	
	void SetInfoFromItem(const QListWidgetItem* item, ToolInfo* info) { infoFromItem.emplace(item, info); }
	MapInfo& GetMapInfo() const { return *mapInfo; }
	const QString& GetMapName() const;
	void AssignMainForm(MainForm* mainForm, QScrollArea* scrollArea);
	void SetMap(const QString& name, size_t width, size_t height);
	void LoadFromFile(const QString& fileName);
	bool SaveToFile(const QString& fileName) const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void ReplaceObject(QPixmap& pixmap, const QRect& rc, ToolInfo* object, ToolInfo*& currentObject);
	void SetMap(MapInfo* mapInfo);
};

#endif    /* _MAPAREA_H */

