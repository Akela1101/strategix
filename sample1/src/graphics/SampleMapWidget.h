#pragma once

#include <Strategix_fwd.h>
#include <Sample_fwd.h>
#include <MapWidget.h>


namespace sample1
{
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
	void OnEntityMoved(IdType id, RealCoord coord);
	void OnEntityMapMoved(MapCoord from, MapCoord to);
	void OnMineRemoved(IdType id);
	
protected:
	void ObjectAdded(MapObject* object) override;
	
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	void ChangeSelection(MapEntity* entity);
};

}
