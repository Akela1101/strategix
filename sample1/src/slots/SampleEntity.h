#pragma once

#include <Sample_fwd.h>
#include <strx/entity/EntitySlot.h>


namespace sample1
{
class SampleEntity : public EntitySlot
{
	SampleMapWidget* mapWidget;

public:
	SampleEntity(s_p<EntityMessage> entityMessage, SampleMapWidget* mapWidget);

private:
	void Moved(RealCoord coord) override;
	void MapMoved(MapCoord from, MapCoord to) override;
	void HpChanged(HpType hp) override;
};
}
