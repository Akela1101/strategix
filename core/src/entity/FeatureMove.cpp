#include "../../strx/EntitySlot.hpp"
#include "../../strx/FeatureInfo.hpp"
#include "../../strx/Map.hpp"
#include "../game/Player.hpp"
#include "../map/MapPath.hpp"
#include "Entity.hpp"

#include "FeatureMove.hpp"


namespace strx
{

FeatureMove::FeatureMove(const FeatureInfo* featureInfo, Entity* entity)
        : Feature(entity)
        , info(dynamic_cast<const MoveFeatureInfo*>(featureInfo))
        , speed(info->speed)
        , next(entity->GetCoord())
{}

FeatureMove::~FeatureMove() = default;

void FeatureMove::Move(s_p<Entity> target, float radius, Feature* mover)
{
	this->target = move(target);
	Move(this->target->GetMapCoord(), radius, mover);
}

void FeatureMove::Move(MapCoord coord, float radius, Feature* mover)
{
	this->coord = coord;
	this->radius = radius;
	this->mover = mover;

	RebuildPath();
	distance = 0;
	terrainQuality = 0;

	entity->AssignTask(this);
}

void FeatureMove::Tick(float seconds)
{
	distance -= seconds * speed * terrainQuality;
	bool isStop = distance <= 0 && !NextPoint();

	RealCoord newCoord = distance > 0 ? next - direction * distance : next;
	entity->SetCoord(newCoord);

	if (isStop)
	{
		entity->AssignTask(nullptr);
		if (mover) mover->Completed(path->IsWhole());
	}
}

void FeatureMove::Stop()
{
	target.reset();
}

bool FeatureMove::NextPoint()
{
	if (path->IsEmpty()) return false;

	RebuildPath();
	if (path->IsEmpty()) return false;

	next = path->TakeNext();
	if (!entity->SetMapCoord(next)) nya_throw << "The first point of the new path is occupied.";

	auto current = entity->GetCoord();
	Player& player = entity->GetPlayer();

	RealCoord delta = (RealCoord) next - current;
	direction = delta.Norm();
	distance += delta.Len();
	terrainQuality = 0.5 * (player.GetTerrain(current)->quality + player.GetTerrain(next)->quality);
	return true;
}

void FeatureMove::RebuildPath()
{
	MapCoord targetCoord = target ? target->GetMapCoord() : coord;
	path = entity->GetPlayer().FindPath(entity->GetMapCoord(), targetCoord, radius);
	if (distance > 0)
	{
		// first point shouldn't be removed, if it's still moving there
		path->AddPoint(entity->GetMapCoord());
	}
}

}  // namespace strx
