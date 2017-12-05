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
	friend class GameWidget;

protected:
	static constexpr int minZoom = 4;
	static constexpr int maxZoom = 64;
	static constexpr int baseTileLen = 64; // size of cell pixmap
	
	Map* map;                     // map related operations
	QScrollArea* scrollArea;      // back link to scroll area
	ToolInfo* tool = nullptr;     // current tool
	int playerNumber = 0;         // current player
	
	u_p<QPixmap> groundPixmap;    // terrain pixmap
	int tileLen = 0;              // cell width | height
	QPoint lastPos;               // last cursor position in map coords
	QPoint lastGlobalPos;         // global position used for scrolling

public:
	MapWidget(QScrollArea* parent);
	~MapWidget() = default;


protected:
	void paintEvent(QPaintEvent*) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent*) override;
	
	void DrawTerrain(const QPixmap& pixmap, const QRect& rc);
	void DrawObject(MapObject* object, QPainter& painter);
	MapObject* CreateObject(int x, int y);
	
private:
	void SetMap(Map* map);
	void CurrentToolChanged(ToolInfo* tool);

signals:
	void MapChanged(bool yes = true);
};

}
#endif //_MapWidget_H
