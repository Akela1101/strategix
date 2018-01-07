#pragma once

#include <Strategix_fwd.h>
#include <Sample_fwd.h>
#include <MapWidget.h>


namespace sample1
{
class SampleMapWidget : public map_info::MapWidget
{
Q_OBJECT
	SampleGame* game = nullptr;
	SamplePlayer* player = nullptr;
	int playerSpot = 0;
	MapEntity* currentEntity = nullptr;
	umap<IdType, MapObject*> mapObjects;

public:
	SampleMapWidget(QScrollArea* parent);
	~SampleMapWidget();

	void Init(SampleGame* game, SamplePlayer* player);
	void ObjectRemoved(IdType id);

public slots:
	void OnEntityMoved(IdType id, RealCoord coord);
	void OnEntityMapMoved(MapCoord from, MapCoord to);

protected:
	void ObjectAdded(MapObject* object) override;

	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	MapObject* GetMapObject(IdType id) const;
	void ChangeSelection(MapEntity* entity);
};

}
