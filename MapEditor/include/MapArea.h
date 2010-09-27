/* 
 * File:   MapArea.h
 * Author: Akela1101
 *
 * Created on 5 Сентябрь 2010 г., 23:41
 */

#ifndef _MAPAREA_H
#define	_MAPAREA_H

#include "Nya.hpp"
#include "MapInfo.h"

#include <QtGui>
#include <QWidget>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

class MainForm;

class MapArea: public QWidget
{
	Q_OBJECT

public:
	std::map<const QListWidgetItem *const, sh_p<ObjectInfo> > objectFromItem;

private:
	MainForm *mainForm;
	QScrollArea *scrollArea;

	sh_p<MapInfo> mapInfo;
	int tileSize;
	sh_p<QPixmap> groundPixmap, frontPixmap;
	QRect lastRc;
	bool isHighlight;

public:
	MapArea(QWidget *parent = 0);
	virtual ~MapArea();

	void SetPs(MainForm *mainForm, QScrollArea *scrollArea);
	void SetMap(sh_p<MapInfo> mapInfo);
	sh_p<MapInfo> GetMapInfo() const;

protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	
private:
	void AddObjectWithPainter(sh_p<QPixmap> &pixmap, const QRect &rc,
		sh_p<ObjectInfo> &obj, const sh_p<ObjectInfo> &newObj);
};

#endif	/* _MAPAREA_H */

