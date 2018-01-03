#include <slots/SampleEntity.h>
#include <slots/SamplePlayer.h>
#include <strx/map/MapObject.h>
#include <strx/map/MapMine.h>
#include <MapInfo.h>
#include <QtGui>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent) : MapWidget(parent) {}
SampleMapWidget::~SampleMapWidget() {}

void SampleMapWidget::AddPlayer(SamplePlayer* player)
{
	player->SetMapWidget(this);

	if (player->GetType() == PlayerType::HUMAN)
	{
		humanPlayerId = player->GetId();
		humanPlayer = player;
	}
}

void SampleMapWidget::OnEntityMoved(IdType id, RealCoord coord)
{
	if (MapObject* object = mapObjects[id])
	{
		update(GetUpdateRect(coord));
		update(GetUpdateRect(object->coord));
		object->coord = coord;
	}
	else error_log << "Entity with id %d does not exist."s % id;
}

void SampleMapWidget::OnEntityMapMoved(MapCoord from, MapCoord to)
{
	auto& object = map->GetCell(to).object;
	if (object)
	{
		error_log << "Trying to replace %s on map."s % object->name;
		return;
	}
	object = std::move(map->GetCell(from).object);
}

void SampleMapWidget::OnMineRemoved(IdType id)
{
	if (MapMine* mine = dynamic_cast<MapMine*>(mapObjects[id]))
	{
		MapCoord coord = mine->coord;
		map->ChangeObject(map->GetCell(coord), nullptr);
		mapObjects.erase(id);
		update(GetUpdateRect(coord));
	}
	else error_log << "Mine with id %d does not exist."s % id;
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
	if (!map->IsCell(coord)) return;

	MapObject* object = map->GetCell(coord).object.get();
	if (object == currentEntity) return;

	// click to empty place -> move
	if (!object)
	{
		if (currentEntity)
		{
			auto& entity = humanPlayer->GetEntitySlot(currentEntity->id);
			entity.Move(coord);
		}
		return;
	}

	// click on mine -> collect
	if (MapMine* mine = dynamic_cast<MapMine*>(object))
	{
		if (currentEntity)
		{
			auto& entity = humanPlayer->GetEntitySlot(currentEntity->id);
			entity.Collect(coord, mine->name);
		}
		return;
	}

	// click on entity -> select or attack
	if (MapEntity* entity = dynamic_cast<MapEntity*>(object))
	{
		if (entity->owner == humanPlayerId)
		{
			ChangeSelection(entity);
			return;
		}

		if (currentEntity)
		{
			// @#~
		}
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
