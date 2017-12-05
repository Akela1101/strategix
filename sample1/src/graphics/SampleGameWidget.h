#ifndef _SampleGameWidget_H
#define _SampleGameWidget_H

#include <MapInfo_Forward.h>
#include <GameWidget.h>


namespace sample1
{
class SampleGameWidget : public map_info::GameWidget
{
	int playerId;
	
public:
	SampleGameWidget(int playerId);
	
protected:
	map_info::MapWidget* CreateMapWidget() override;
};
}

#endif //_SampleGameWidget_H
