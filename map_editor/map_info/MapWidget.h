#pragma once

#include <MapInfo_fwd.h>
#include <QWidget>
#include <Strategix_fwd.h>


class QScrollArea;

namespace map_info
{
class MapWidget : public QWidget
{
	Q_OBJECT
protected:
	static constexpr int minZoom = 4;
	static constexpr int maxZoom = 64;
	static constexpr int baseTileLen = 64;  // size of cell pixmap

	s_p<Map> map;             // map related operations
	QScrollArea* scrollArea;  // back link to scroll area

	u_p<QPixmap> groundPixmap;  // terrain pixmap
	int tileLen = 0;            // cell width | height
	QPoint lastGlobalPos;       // global position used for scrolling

public:
	MapWidget(QScrollArea* parent);

	void SetMap(s_p<Map> newMap);

protected:
	virtual void ObjectAdded(MapObject* object) {}

	void paintEvent(QPaintEvent*) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void DrawTerrain(const QPixmap& pixmap, const QRect& rc);
	virtual void DrawObject(MapObject* object, QPainter& painter);
	virtual QRect GetUpdateRect(RealCoord coord);
	static QRect GetBaseRect(RealCoord coord);

signals:
	void MapChanged(bool yes = true);
};

}  // namespace map_info
