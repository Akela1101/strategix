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
	SamplePlayer* humanPlayer = nullptr;
	int humanPlayerId = 0;
	MapEntity* currentEntity = nullptr;

	umap<int, MapObject*> mapObjects;

public:
	SampleMapWidget(QScrollArea* parent);
	~SampleMapWidget();

	void Init(SampleGame* game, SamplePlayer* humanPlayer);

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
