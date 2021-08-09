#include <MapInfo.h>
#include <QtGui>
#include <slots/SampleEntity.h>
#include <slots/SampleGame.h>
#include <slots/SamplePlayer.h>
#include <strx/map/MapMine.h>
#include <strx/map/MapObject.h>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent) : MapWidget(parent) {}
SampleMapWidget::~SampleMapWidget() {}

MapObject* SampleMapWidget::GetMapObject(IdType id) const
{
	try
	{
		return mapObjects.at(id);
	}
	catch (out_of_range&)
	{
		error_log << "Object with id %d does not exist."s % id;
		return nullptr;
	}
}

void SampleMapWidget::Init(SampleGame* game, SamplePlayer* player)
{
	this->game = game;
	this->player = player;
	playerSpot = player->GetSpot();
}

void SampleMapWidget::ObjectRemoved(IdType id)
{
	if (MapObject* object = GetMapObject(id))
	{
		MapCoord coord = object->coord;
		map->ChangeObject(map->GetCell(coord), nullptr);
		mapObjects.erase(id);
		if (currentEntity && currentEntity->id == id) currentEntity = nullptr;

		update(GetUpdateRect(coord));
	}
}

void SampleMapWidget::OnEntityMoved(IdType id, RealCoord coord)
{
	if (MapObject* object = GetMapObject(id))
	{
		update(GetUpdateRect(coord));
		update(GetUpdateRect(object->coord));
		object->coord = coord;
	}
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

void SampleMapWidget::OnEntityHpChanged(IdType id, HpType hp)
{
	if (auto entity = (MapEntity*) GetMapObject(id))
	{
		entity->hp = hp;
		update(GetUpdateRect(entity->coord));
	}
}

void SampleMapWidget::ObjectAdded(MapObject* object)
{
	mapObjects.emplace(object->id, object);
}

void SampleMapWidget::DrawObject(MapObject* object, QPainter& painter)
{
	MapWidget::DrawObject(object, painter);

	// hp bar
	if (auto mapEntity = dynamic_cast<MapEntity*>(object))
	{
		QRect rc = GetBaseRect(object->coord);
		int width = (rc.width() - 6) * mapEntity->hp / mapEntity->maxHp;
		QRect barRc{rc.left() + 3, rc.top() - 15, width, 10};

		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.setBrush(QColor(100, 255, 100));
		painter.drawRect(barRc);
	}
}

QRect SampleMapWidget::GetUpdateRect(RealCoord coord)
{
	QRect rc = MapWidget::GetUpdateRect(coord);
	return rc.adjusted(0, -16, 0, 0);  // hp bar
}

void SampleMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);

	if (currentEntity)  // selection box
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
			auto& entitySlot = game->GetEntitySlot(currentEntity->id);
			entitySlot.Move(coord);
		}
		return;
	}

	// click on mine -> collect
	if (MapMine* mine = dynamic_cast<MapMine*>(object))
	{
		if (currentEntity)
		{
			auto& entitySlot = game->GetEntitySlot(currentEntity->id);
			entitySlot.Collect(coord, mine->name);
		}
		return;
	}

	// click on entity -> select or attack
	if (MapEntity* entity = dynamic_cast<MapEntity*>(object))
	{
		if (entity->ownerSpot == playerSpot)
		{
			ChangeSelection(entity);
			return;
		}

		if (currentEntity)
		{
			auto& entitySlot = game->GetEntitySlot(currentEntity->id);
			entitySlot.Attack(entity->id);
		}
	}
}

void SampleMapWidget::ChangeSelection(MapEntity* entity)
{
	if (currentEntity) update(GetUpdateRect(currentEntity->coord));

	currentEntity = entity;
	update(GetUpdateRect(entity->coord));
}

}  // namespace sample1
