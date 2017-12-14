#include <slots/SampleEntiSlot.h>
#include <slots/SamplePlayerSlot.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapMine.h>
#include <MapInfo.h>
#include <QtGui>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent) : MapWidget(parent) {}
SampleMapWidget::~SampleMapWidget() {}

void SampleMapWidget::AddPlayer(SamplePlayerSlot* playerSlot)
{
	playerSlot->SetMapWidget(this);

	if (playerSlot->GetType() == PlayerType::HUMAN)
	{
		humanPlayerId = playerSlot->GetId();
		humanPlayer = playerSlot;
		
		mapCopy.reset(new Map(playerSlot->GetMap()));
		SetMap(mapCopy.get());
	}
}

void SampleMapWidget::OnEntityMoved(int entityId, RealCoord coord)
{
	if (!in_(entityId, mapObjects))
	{
		error_log << "Entity [%d] is not found on map."s % entityId;
		return;
	}
	
	MapObject* object = mapObjects.at(entityId);
	MapCoord mapCoord = object->coord;
	MapCoord currentMapCoord = coord;
	if (mapCoord != currentMapCoord)
	{
		auto&& uObject = map->GetCell(mapCoord).object;
		auto& currentObject = map->GetCell(currentMapCoord).object;
		if (currentObject)
		{
			error_log << "Trying to replace %s on map."s % currentObject->name;
			return;
		}
		currentObject = std::move(uObject);
	}
	update(GetUpdateRect(coord));
	update(GetUpdateRect(object->coord));
	object->coord = coord;
}

void SampleMapWidget::ObjectAdded(MapObject* object)
{
	mapObjects.emplace(object->id, object);
}

void SampleMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);
	
	if (currentEntity) // selection box
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
	if (!(event->buttons() & Qt::LeftButton)) return;
	
	QPoint point = event->pos();
	MapCoord coord(point.x() / tileLen, point.y() / tileLen);
	
	MapObject* object = map->GetCell(coord).object.get();
	if (object == currentEntity) return;
	
	// click to empty place -> move
	if (!object)
	{
		auto& entity = humanPlayer->GetEntitySlot(currentEntity->id);
		entity.DoMove(coord);
		return;
	}
	
	// click on mine -> collect
	if (MapMine* mine = dynamic_cast<MapMine*>(object))
	{
		auto& entity = humanPlayer->GetEntitySlot(currentEntity->id);
		entity.DoCollect(coord, mine->name);
		return;
	}
	
	// click on own entity -> select
	if (MapEntity* entity = dynamic_cast<MapEntity*>(object))
	{
		if (entity->owner == humanPlayerId)
		{
			ChangeSelection(entity);
			return;
		}
		
		// click on enemy entity -> attack
		// @#~
	}
}

void SampleMapWidget::ChangeSelection(MapEntity* entity)
{
	if (currentEntity)
	{
		update(GetUpdateRect(currentEntity->coord));
	}
	currentEntity = entity;
	update(GetUpdateRect(entity->coord));
}

}
