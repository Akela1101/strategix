#ifndef _SampleMapWidget_H
#define _SampleMapWidget_H

#include <Strategix_Forward.h>
#include <Sample_Forward.h>
#include <MapWidget.h>


namespace sample1
{
using namespace strx;

class SampleMapWidget : public map_info::MapWidget
{
	u_p<Map> mapCopy;
	int humanPlayerId = 0;
	EntityObject* currentEntity = nullptr;
	SamplePlayerSlot* humanPlayer = nullptr;
	
public:
	SampleMapWidget(QScrollArea* parent);
	~SampleMapWidget();
	
	void AddPlayer(SamplePlayerSlot* playerSlot);

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	void ChangeSelection(EntityObject* entity);
};

}

#endif //_SampleMapWidget_H
