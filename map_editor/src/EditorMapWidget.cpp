#include <MapInfo.h>
#include <QScrollArea>
#include <QtGui>
#include <strx/map/MapMine.h>
#include <strx/map/MapObject.h>

#include "EditorMapWidget.h"


namespace map_editor
{
void EditorMapWidget::CurrentToolChanged(ToolInfo* tool)
{
	this->tool = tool;
}

void EditorMapWidget::CurrentPlayerChanged(int playerSpot)
{
	this->playerSpot = playerSpot;
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
	if (event->buttons() & Qt::LeftButton) grabMouse();

	UpdateUnderMouse(event);  // single mouse click

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
	if (!(event->buttons() & Qt::LeftButton))  //
	{
		isHighlight = true;
	}
	else
	{
		isHighlight = false;
		if (tool)
		{
			if (tool->type == ToolType::TERRAIN)  //
			{
				ChangeTerrain(coord);
			}
			else
			{
				ChangeObject(coord);
			}
			update(rc);
			emit MapChanged();
		}
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

void EditorMapWidget::ChangeTerrain(MapCoord coord)
{
	auto& cell = map->GetCell(coord);
	if (cell.terrain->name != tool->name)
	{
		map->ChangeTerrain(cell, tool->name);
		DrawTerrain(tool->image, GetBaseRect(coord));
	}
}

void EditorMapWidget::ChangeObject(MapCoord coord)
{
	auto& cell = map->GetCell(coord);
	IdType id = Map::GetNextId();
	switch (tool->type)
	{
		case ToolType::ENTITY: map->ChangeObject(cell, make_u<MapEntity>(id, tool->name, coord, playerSpot));
		case ToolType::MINE: map->ChangeObject(cell, make_u<MapMine>(id, tool->name, coord, 1000));
	}
}

}  // namespace map_editor
