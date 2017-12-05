#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>
#include <QScrollArea>

#include "EditorMapWidget.h"


namespace map_editor
{
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
		QRect baseRc = GetBaseRect(QPoint(point.x() / tileLen, point.y() / tileLen));
		
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

QRect EditorMapWidget::GetBaseRect(QPoint pos)
{
	return QRect(pos.x() * baseTileLen, pos.y() * baseTileLen, baseTileLen, baseTileLen);
}

void EditorMapWidget::UpdateUnderMouse(QMouseEvent* event)
{
	if (!map) return;
	
	QPoint point = event->pos();
	if (!this->rect().contains(point)) return;
	
	QPoint pos(point.x() / tileLen, point.y() / tileLen);
	QRect rc = QRect(pos.x() * tileLen, pos.y() * tileLen, tileLen, tileLen);
	
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
				DrawTerrain(tool->image, GetBaseRect(pos));
			}
		}
		else
		{
			auto&& object = CreateObject(pos.x(), pos.y());
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
	if (lastPos != pos)
	{
		update(lastRc);
		update(rc);
		lastRc = rc;
		lastPos = pos;
	}
}

}

