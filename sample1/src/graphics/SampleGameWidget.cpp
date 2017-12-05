#include <graphics/SampleMapWidget.h>

#include "SampleGameWidget.h"


namespace sample1
{
SampleGameWidget::SampleGameWidget(int playerId)
	: playerId(playerId)
{}

map_info::MapWidget* SampleGameWidget::CreateMapWidget()
{
	return new SampleMapWidget(this, playerId);
}
}
