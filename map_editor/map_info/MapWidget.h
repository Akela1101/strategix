#ifndef _MapWidget_H
#define _MapWidget_H

#include <MapInfo_Forward.h>
#include <Strategix_Forward.h>
#include <QWidget>


class QScrollArea;

namespace map_info
{
using namespace strx;

class MapWidget : public QWidget
{
Q_OBJECT
protected:
	static constexpr int minZoom = 4;
	static constexpr int maxZoom = 64;
	static constexpr int baseTileLen = 64; // size of cell pixmap
	
	Map* map;                     // map related operations
	QScrollArea* scrollArea;      // back link to scroll area
	
	u_p<QPixmap> groundPixmap;    // terrain pixmap
	int tileLen = 0;              // cell width | height
	QPoint lastGlobalPos;         // global position used for scrolling

public:
	MapWidget(QScrollArea* parent);
	~MapWidget() = default;
	
	void SetMap(Map* map);

protected:
	virtual void ObjectAdded(MapObject* object) {}
	
	void paintEvent(QPaintEvent*) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent*) override;
	
	void DrawTerrain(const QPixmap& pixmap, const QRect& rc);
	void DrawObject(MapObject* object, QPainter& painter);
	QRect GetUpdateRect(RealCoord coord);
	static QRect GetBaseRect(RealCoord coord);
	
signals:
	void MapChanged(bool yes = true);
};

}
#endif //_MapWidget_H
