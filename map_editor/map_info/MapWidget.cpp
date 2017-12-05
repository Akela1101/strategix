#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>
#include <QScrollArea>
#include <QScrollBar>

#include "MapWidget.h"


namespace map_info
{
using namespace strx;


MapWidget::MapWidget(QScrollArea* parent)
		: QWidget(parent)
		, scrollArea(parent)
{
	setMouseTracking(true);
}

void MapWidget::paintEvent(QPaintEvent* event)
{
	if (!map) return;
	
	qreal scale = (qreal) tileLen / baseTileLen;
	
	// update terrain
	QPainter painter(this);
	painter.scale(scale, scale);
	painter.drawPixmap(0, 0, *groundPixmap);
	
	// update affected objects;
	QRect rc = event->rect();
	int fromX = rc.left() / tileLen;
	int fromY = rc.top() / tileLen;
	int tillX = rc.right() / tileLen;
	int tillY = rc.bottom() / tileLen;
	for (int row = fromY; row <= tillY; ++row)
	{
		for (int col = fromX; col <= tillX; ++col)
		{
			MapObject* object = map->GetCell(col, row).object.get();
			DrawObject(object, painter);
		}
	}
}

void MapWidget::wheelEvent(QWheelEvent* event)
{
	if (!map) return;
	
	tileLen += copysign(4, event->delta());
	if (tileLen < minZoom)
	{
		tileLen = minZoom;
		return;
	}
	if (tileLen > maxZoom)
	{
		tileLen = maxZoom;
		return;
	}
	
	// Update view
	setFixedSize(groundPixmap->size() * tileLen / baseTileLen);
	update();
	
	// Move sliders to mouse center
	QScrollBar* hSB = scrollArea->horizontalScrollBar();
	int tilesNumberX = hSB->pageStep() / maxZoom;      // number of tiles on screen for max zoom
	int centralWidth = map->GetWidth() - tilesNumberX;  // number of tiles in the center of screen
	int centralX = lastPos.x() - tilesNumberX / 2;     // position in central coordinates
	if (centralWidth < 1) centralWidth = 1;
	hSB->setSliderPosition(hSB->maximum() * centralX / centralWidth);
	
	QScrollBar* vSB = scrollArea->verticalScrollBar();
	int tilesNumberY = vSB->pageStep() / maxZoom;
	int centralHeight = map->GetLength() - tilesNumberY;
	int centralY = lastPos.y() - tilesNumberY / 2;
	if (centralHeight < 1) centralHeight = 1;
	vSB->setSliderPosition(vSB->maximum() * centralY / centralHeight);
}

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
	// Move sliders
	if (event->buttons() & Qt::RightButton)
	{
		QPoint globalPos = event->globalPos();
		
		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		hSB->setSliderPosition(hSB->sliderPosition() - globalPos.x() + lastGlobalPos.x());
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		vSB->setSliderPosition(vSB->sliderPosition() - globalPos.y() + lastGlobalPos.y());
		
		lastGlobalPos = globalPos;
	}
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
	lastGlobalPos = event->globalPos();
	if (event->buttons() & Qt::RightButton)
	{
		grabMouse(QCursor(Qt::ClosedHandCursor));
	}
}

void MapWidget::mouseReleaseEvent(QMouseEvent*)
{
	releaseMouse();
}

void MapWidget::DrawTerrain(const QPixmap& pixmap, const QRect& rc)
{
	QPainter painter(groundPixmap.get());
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.drawPixmap(rc, pixmap);
}

void MapWidget::DrawObject(MapObject* object, QPainter& painter)
{
	if (!object) return;
	
	auto&& tool = MapInfo::objectTools[object->name];
	RealCoord coord = object->coord;
	QRect rc(baseTileLen * (coord.x - 0.5), baseTileLen * (coord.y - 0.5), baseTileLen, baseTileLen);
	painter.drawPixmap(rc, tool.image);
	
	if (tool.type == ToolType::ENTITY)
	{
		auto entityObject = (EntityObject*) object;
		int w = rc.width(), h = rc.height();
		QRect markRc = rc.adjusted(0, 0, -w / 2, -h / 2);
		
		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.drawPixmap(markRc, MapInfo::GetPlayerMark(entityObject->owner));
	}
}

MapObject* MapWidget::CreateObject(int x, int y)
{
	if (!tool) return nullptr;
	
	MapCoord coord(x, y);
	switch (tool->type)
	{
		case ToolType::ENTITY:
			return new EntityObject{ tool->name, coord, playerNumber };
		case ToolType::MINE:
			return new MineObject{ tool->name, coord, 1000 };
	}
	return nullptr;
}

void MapWidget::SetMap(Map* map)
{
	this->map = map;
	int width = map->GetWidth();
	int height = map->GetLength();
	QSize groundSize(width * baseTileLen, height * baseTileLen);
	groundPixmap.reset(new QPixmap(groundSize));
	
	// Draw ground and objects
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto rc = QRect(col * baseTileLen, row * baseTileLen, baseTileLen, baseTileLen);
			auto&& cell = map->GetCell(col, row);
			
			auto&& tool = MapInfo::terrainTools[cell.terrain->name];
			DrawTerrain(tool.image, rc);
		}
	}
	
	tileLen = baseTileLen / 2;
	setFixedSize(groundSize * tileLen / baseTileLen);
	update();
}

void MapWidget::CurrentToolChanged(ToolInfo* tool)
{
	this->tool = tool;
}

}

