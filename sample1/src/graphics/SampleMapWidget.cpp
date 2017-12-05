#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent, int playerId)
		: MapWidget(parent)
		, playerId(playerId)
{}

void SampleMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);
	
	if (currentEntity)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::green));
		
		auto coord = currentEntity->coord;
		int len = tileLen - painter.pen().width();
		QRect rc(tileLen * coord.x - len * 0.5, tileLen * coord.y - len* 0.5, len, len);
		
		painter.drawRect(rc);
	}
}

void SampleMapWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		QPoint point = event->pos();
		MapCoord coord(point.x() / tileLen, point.y() / tileLen);
		
		MapObject* object = map->GetCell(coord).object.get();
		EntityObject* entity = dynamic_cast<EntityObject*>(object);
		if (entity && entity->owner == playerId)
		{
			if (currentEntity)
			{
				update(GetRect(currentEntity->coord));
			}
			currentEntity = entity;
			update(GetRect(coord));
		}
	}
	MapWidget::mousePressEvent(event);
}

}
