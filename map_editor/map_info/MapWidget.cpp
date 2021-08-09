#include <MapInfo.h>
#include <QScrollArea>
#include <QScrollBar>
#include <QtGui>
#include <strx/map/MapObject.h>

#include "MapWidget.h"


namespace map_info
{
MapWidget::MapWidget(QScrollArea* parent) : QWidget(parent), scrollArea(parent)
{
	setMouseTracking(true);
}

void MapWidget::SetMap(s_p<Map> newMap)
{
	map = std::move(newMap);
	if (!map) return;

	int width = map->GetWidth();
	int height = map->GetLength();
	QSize groundSize(width * baseTileLen, height * baseTileLen);
	groundPixmap.reset(new QPixmap(groundSize));

	// Draw ground and objects
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			auto rc = QRect(col * baseTileLen, row * baseTileLen, baseTileLen, baseTileLen);
			const auto& cell = map->GetCell(col, row);

			const auto& tool = MapInfo::terrainTools[cell.terrain->name];
			DrawTerrain(tool.image, rc);

			if (cell.object) { ObjectAdded(cell.object.get()); }
		}
	}

	tileLen = baseTileLen / 2;
	setFixedSize(groundSize * tileLen / baseTileLen);
	update();
}

void MapWidget::paintEvent(QPaintEvent* event)
{
	if (!map) return;

	qreal scale = (qreal) tileLen / baseTileLen;

	// update terrain
	QPainter painter(this);
	painter.scale(scale, scale);
	painter.drawPixmap(0, 0, *groundPixmap);

	// update affected objects
	QRect rc = event->rect();
	int fromX = max(0, rc.left() / tileLen - 1);
	int fromY = max(0, rc.top() / tileLen - 1);
	int tillX = min(map->GetWidth() - 1, rc.right() / tileLen + 1);
	int tillY = min(map->GetLength() - 1, rc.bottom() / tileLen + 1);

	for (int row = fromY; row <= tillY; ++row)
	{
		for (int col = fromX; col <= tillX; ++col)
		{
			MapObject* object = map->GetCell(col, row).object.get();
			DrawObject(object, painter);
		}
	}
}

void MapWidget::wheelEvent(QWheelEvent* event)
{
	if (!map) return;

	tileLen += copysign(4, event->angleDelta().y());
	if (tileLen < minZoom)
	{
		tileLen = minZoom;
		return;
	}
	if (tileLen > maxZoom)
	{
		tileLen = maxZoom;
		return;
	}

	// Update view
	setFixedSize(groundPixmap->size() * tileLen / baseTileLen);
	update();

	QPointF point = event->pos() / tileLen;

	// Move sliders to mouse center
	QScrollBar* hSB = scrollArea->horizontalScrollBar();
	int tilesNumberX = hSB->pageStep() / maxZoom;       // number of tiles on screen for max zoom
	int centralWidth = map->GetWidth() - tilesNumberX;  // number of tiles in the center of screen
	int centralX = point.x() - tilesNumberX / 2;        // position in central coordinates
	if (centralWidth < 1) centralWidth = 1;
	hSB->setSliderPosition(hSB->maximum() * centralX / centralWidth);

	QScrollBar* vSB = scrollArea->verticalScrollBar();
	int tilesNumberY = vSB->pageStep() / maxZoom;
	int centralHeight = map->GetLength() - tilesNumberY;
	int centralY = point.y() - tilesNumberY / 2;
	if (centralHeight < 1) centralHeight = 1;
	vSB->setSliderPosition(vSB->maximum() * centralY / centralHeight);
}

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
	// Move sliders
	if (event->buttons() & Qt::RightButton)
	{
		QPoint globalPos = event->globalPos();

		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		hSB->setSliderPosition(hSB->sliderPosition() - globalPos.x() + lastGlobalPos.x());
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		vSB->setSliderPosition(vSB->sliderPosition() - globalPos.y() + lastGlobalPos.y());

		lastGlobalPos = globalPos;
	}
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
	lastGlobalPos = event->globalPos();
	if (event->buttons() & Qt::RightButton) { grabMouse(QCursor(Qt::ClosedHandCursor)); }
}

#include <QApplication>
void MapWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (!(event->buttons() & Qt::RightButton))
	{
		releaseMouse();
		QApplication::setOverrideCursor(
		        QCursor(Qt::ArrowCursor));  // @#~ should do it automatically on releaseMouse() < qt-5.10 bug? >
	}
}

void MapWidget::DrawTerrain(const QPixmap& pixmap, const QRect& rc)
{
	QPainter painter(groundPixmap.get());
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.drawPixmap(rc, pixmap);
}

void MapWidget::DrawObject(MapObject* object, QPainter& painter)
{
	if (!object) return;

	auto&& tool = MapInfo::objectTools[object->name];
	QRect rc = GetBaseRect(object->coord);
	painter.drawPixmap(rc, tool.image);

	if (auto mapEntity = dynamic_cast<MapEntity*>(object))  // player geo-tag
	{
		int w = rc.width(), h = rc.height();
		QRect markRc = rc.adjusted(0, 0, -w / 2, -h / 2);

		painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.drawPixmap(markRc, MapInfo::GetPlayerMark(mapEntity->ownerSpot));
	}
}

QRect MapWidget::GetUpdateRect(RealCoord coord)
{
	return QRect(tileLen * (coord.x - 0.55), tileLen * (coord.y - 0.55), tileLen * 1.1, tileLen * 1.1);
}

QRect MapWidget::GetBaseRect(RealCoord coord)
{
	return QRect((coord.x - 0.5) * baseTileLen, (coord.y - 0.5) * baseTileLen, baseTileLen, baseTileLen);
}

}  // namespace map_info
