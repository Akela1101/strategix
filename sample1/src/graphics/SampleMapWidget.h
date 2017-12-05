#ifndef _SampleMapWidget_H
#define _SampleMapWidget_H

#include <Strategix_Forward.h>
#include <MapWidget.h>


namespace sample1
{
using namespace strx;

class SampleMapWidget : public map_info::MapWidget
{
	int playerId;
	EntityObject* currentEntity = nullptr;
	
public:
	SampleMapWidget(QScrollArea* parent, int playerId);

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;
};

}

#endif //_SampleMapWidget_H
