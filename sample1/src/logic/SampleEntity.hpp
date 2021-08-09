#pragma once

#include <sample1_fwd.hpp>
#include <strx/Entity.hpp>


namespace sample1
{
class SampleEntity : public Entity
{
	SampleMapWidget* mapWidget;

public:
	SampleEntity(s_p<EntityMessage> entityMessage, SampleMapWidget* mapWidget);

private:
	void Moved(RealCoord coord) override;
	void MapMoved(MapCoord from, MapCoord to) override;
	void HpChanged(HpType hp) override;
};
}  // namespace sample1
