#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>
#include <QScrollArea>

#include "EditorMapWidget.h"


namespace map_editor
{
void EditorMapWidget::CurrentToolChanged(ToolInfo* tool)
{
	this->tool = tool;
}

void EditorMapWidget::CurrentPlayerChanged(int playerId)
{
	this->playerId = playerId;
}

void EditorMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);
	
	if (!map) return;
	
	qreal scale = (qreal) tileLen / baseTileLen;
	
	QPainter painter(this);
	painter.scale(scale, scale);
	if (isHighlight)
	{
		QPoint point = mapFromGlobal(QCursor::pos());
		QRect baseRc = GetBaseRect(MapCoord(point.x() / tileLen, point.y() / tileLen));
		
		painter.setBrush(QColor(250, 250, 100, 150));
		painter.setPen(Qt::NoPen);
		painter.drawRect(baseRc);
	}
}

void EditorMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	UpdateUnderMouse(event);
	
	MapWidget::mouseMoveEvent(event);
}

void EditorMapWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		grabMouse();
	}
	UpdateUnderMouse(event); // single mouse click
	
	MapWidget::mousePressEvent(event);
}

void EditorMapWidget::UpdateUnderMouse(QMouseEvent* event)
{
	if (!map) return;
	
	QPoint point = event->pos();
	if (!this->rect().contains(point)) return;
	
	MapCoord coord(point.x() / tileLen, point.y() / tileLen);
	QRect rc = QRect(coord.x * tileLen, coord.y * tileLen, tileLen, tileLen);
	
	// Draw objects, if LMB and current item is valid.
	if (event->buttons() & Qt::LeftButton)
	{
		isHighlight = false;
		
		auto& cell = map->GetCell(coord.x, coord.y);
		if (tool && tool->type == ToolType::TERRAIN)
		{
			if (cell.terrain->name != tool->name)
			{
				map->ChangeTerrain(cell, tool->name);
				DrawTerrain(tool->image, GetBaseRect(coord));
			}
		}
		else
		{
			auto&& object = CreateObject(coord.x, coord.y);
			map->ChangeObject(cell, object);
		}
		update(rc);
		emit MapChanged();
	}
	else // Highlight current rectangle
	{
		isHighlight = true;
	}
	
	// Update rects
	if (lastCoord != coord)
	{
		update(lastRc);
		update(rc);
		lastRc = rc;
		lastCoord = coord;
	}
}

MapObject* EditorMapWidget::CreateObject(int x, int y)
{
	if (!tool) return nullptr;
	
	MapCoord coord(x, y);
	switch (tool->type)
	{
		case ToolType::ENTITY:
			return new MapEntity{ tool->name, coord, playerId };
		case ToolType::MINE:
			return new MapMine{ tool->name, coord, 1000 };
	}
	return nullptr;
}

}

