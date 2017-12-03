#include <graphics/SampleMapWidget.h>

#include "SampleGameWidget.h"


namespace sample1
{
map_info::MapWidget* SampleGameWidget::CreateMapWidget()
{
	return new SampleMapWidget(this);
}
}
