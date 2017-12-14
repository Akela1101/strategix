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
Q_OBJECT
	u_p<Map> mapCopy;
	int humanPlayerId = 0;
	MapEntity* currentEntity = nullptr;
	SamplePlayerSlot* humanPlayer = nullptr;
	
	umap<int, MapObject*> mapObjects;
	
public:
	SampleMapWidget(QScrollArea* parent);
	~SampleMapWidget();
	
	void AddPlayer(SamplePlayerSlot* playerSlot);

public slots:
	void OnEntityMoved(int entityId, RealCoord coord);
	
protected:
	void ObjectAdded(MapObject* object) override;
	
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	void ChangeSelection(MapEntity* entity);
};

}

#endif //_SampleMapWidget_H
