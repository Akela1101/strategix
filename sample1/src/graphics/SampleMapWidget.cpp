#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>
#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent) : MapWidget(parent) {}
SampleMapWidget::~SampleMapWidget() {}

void SampleMapWidget::AddPlayer(SamplePlayerSlot* playerSlot)
{
	if (playerSlot->GetType() == PlayerType::HUMAN)
	{
		humanPlayerId = playerSlot->GetId();
		humanPlayer = playerSlot;
		
		mapCopy.reset(new Map(playerSlot->GetMap()));
		SetMap(mapCopy.get());
	}
}

void SampleMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);
	
	if (currentEntity)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::green));
		
		auto coord = currentEntity->coord;
		int len = tileLen - painter.pen().width();
		auto rc = QRect(tileLen * coord.x - len * 0.5, tileLen * coord.y - len * 0.5, len, len);
		
		painter.drawRect(rc);
	}
}

void SampleMapWidget::mousePressEvent(QMouseEvent* event)
{
	MapWidget::mousePressEvent(event);
	if (!(event->buttons() & Qt::LeftButton))
	{
		return;
	}
	
	QPoint point = event->pos();
	MapCoord coord(point.x() / tileLen, point.y() / tileLen);
	
	MapObject* object = map->GetCell(coord).object.get();
	if (!object)
	{
		auto& entity = humanPlayer->GetEntity(currentEntity->id);
		entity.DoMove(coord);
		return;
	}
	
	EntityObject* entity = dynamic_cast<EntityObject*>(object);
	if (!entity)
	{
		// Collect
		return;
	}
	
	if (entity == currentEntity)
	{
		return;
	}
	
	if (entity->owner == humanPlayerId)
	{
		ChangeSelection(entity);
		return;
	}
	
	// Attack
}

void SampleMapWidget::ChangeSelection(EntityObject* entity)
{
	if (currentEntity)
	{
		update(GetRect(currentEntity->coord));
	}
	currentEntity = entity;
	update(GetRect(entity->coord));
}

}
