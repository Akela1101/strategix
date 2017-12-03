#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>
#include <QScrollArea>

#include "EditorMapWidget.h"


namespace map_editor
{
void EditorMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (!map) return;
	
	const QPoint& point = event->pos();
	if (!this->rect().contains(point)) return;
	
	QPoint pos(point.x() / tileLen, point.y() / tileLen);
	rectBase = QRect(pos.x() * tileLenBase, pos.y() * tileLenBase, tileLenBase, tileLenBase);
	
	// Draw objects, if LMB and current item is valid.
	if (event->buttons() & Qt::LeftButton)
	{
		isHighlight = false;
		
		auto& cell = map->GetCell(pos.x(), pos.y());
		if (tool && tool->type == ToolType::TERRAIN)
		{
			if (cell.terrain->name != tool->name)
			{
				map->ChangeTerrain(cell, tool->name);
				DrawTerrain(tool->image, rectBase);
			}
		}
		else
		{
			auto&& object = CreateObject(pos.x(), pos.y());
			
			map->ChangeObject(cell, object);
			DrawObject(object, rectBase);
		}
		update(rectBase);
		emit MapChanged();
	}
	else // Highlight current rectangle
	{
		isHighlight = true;
	}
	
	// Update rects
	QRect newRectScaled = QRect(pos.x() * tileLen, pos.y() * tileLen, tileLen, tileLen);
	if (lastPos != pos)
	{
		update(rectScaled);
		update(newRectScaled);
		rectScaled = newRectScaled;
		lastPos = pos;
	}
	
	MapWidget::mouseMoveEvent(event);
}

void EditorMapWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		grabMouse();
	}
	mouseMoveEvent(event); // for single mouse click processing
	
	MapWidget::mousePressEvent(event);
}
}

