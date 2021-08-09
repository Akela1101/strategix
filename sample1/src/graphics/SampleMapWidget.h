#pragma once

#include <MapWidget.h>
#include <Sample_fwd.h>
#include <Strategix_fwd.h>


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
	~SampleMapWidget() override;

	MapObject* GetMapObject(IdType id) const;
	void Init(SampleGame* game, SamplePlayer* player);
	void ObjectRemoved(IdType id);

public slots:
	void OnEntityMoved(IdType id, RealCoord coord);
	void OnEntityMapMoved(MapCoord from, MapCoord to);
	void OnEntityHpChanged(IdType id, HpType hp);

protected:
	void ObjectAdded(MapObject* object) override;
	void DrawObject(MapObject* object, QPainter& painter) override;
	QRect GetUpdateRect(RealCoord coord) override;

	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	void ChangeSelection(MapEntity* entity);
};

}  // namespace sample1
