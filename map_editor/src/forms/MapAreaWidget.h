#ifndef _MAPAREA_H
#define	_MAPAREA_H

#include <nya.hpp>
#include "MapInfo.h"

#include <QtGui>
#include <QWidget>
#include <QListWidgetItem>
#include <QScrollArea>
#include <map>
#include <string>

class MainForm;

class MapAreaWidget: public QWidget
{
	Q_OBJECT

public:
	std::map<const QListWidgetItem *const, s_p<ObjectInfo>> objectFromItem;

private:
	MainForm *mainForm;
	QScrollArea *scrollArea;

	s_p<MapInfo> mapInfo;
	int tileSize;
	s_p<QPixmap> groundPixmap, frontPixmap;
	QRect lastRc;
	bool isHighlight;

public:
	MapAreaWidget(QWidget *parent = nullptr);

	void SetPs(MainForm *mainForm, QScrollArea *scrollArea);
	void SetMap(s_p<MapInfo>& mapInfo);
	s_p<MapInfo> GetMapInfo() const;

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	
private:
	void AddObjectWithPainter(s_p<QPixmap> &pixmap, const QRect &rc,
		s_p<ObjectInfo> &obj, const s_p<ObjectInfo> &newObj);
};

#endif	/* _MAPAREA_H */

