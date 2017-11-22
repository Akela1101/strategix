#include <QtGui>
#include <QScrollBar>
#include <MapInfo.h>

#include "MapAreaWidget.h"


namespace map_info
{
static constexpr int minZoom = 4;
static constexpr int maxZoom = 64;
static constexpr int tileLenBase = 64; // size of tile pixmap

class MapAreaWidgetImpl : public QWidget
{
Q_OBJECT
	friend class MapAreaWidget;
	
	QScrollArea* scrollArea;
	ToolInfo* tool;
	u_p<MapInfo> mapInfo;
	u_p<QPixmap> groundPixmap;
	u_p<QPixmap> frontPixmap;
	QRect rectBase;
	QRect rectScaled;
	QPoint lastPos;
	QPoint globalPos;
	QPoint lastGlobalPos;
	int tileLen;
	bool isHighlight;

public:
	MapAreaWidgetImpl(QScrollArea* parent)
			: QWidget(parent)
			, scrollArea(parent)
			, isHighlight(false)
	{
		setMouseTracking(true);
	}
	
	~MapAreaWidgetImpl() = default;


protected:
	void paintEvent(QPaintEvent*) override
	{
		if (!mapInfo) return;
		
		qreal scale = (qreal) tileLen / tileLenBase;
		
		QPainter painter(this);
		painter.scale(scale, scale);
		painter.drawPixmap(0, 0, *groundPixmap);
		painter.drawPixmap(0, 0, *frontPixmap);
		
		if (isHighlight)
		{
			painter.setBrush(QColor(250, 250, 100, 150));
			painter.setPen(Qt::NoPen);
			painter.drawRect(rectBase);
		}
	}
	
	void wheelEvent(QWheelEvent* event) override
	{
		if (!mapInfo) return;
		
		tileLen += copysign(4, event->delta());
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
		isHighlight = false;
		setFixedSize(groundPixmap->size() * tileLen / tileLenBase);
		update();
		
		// Move sliders to mouse center
		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		int tilesNumberX = hSB->pageStep() / maxZoom;      // number of tiles on screen for max zoom
		int centralWidth = mapInfo->width - tilesNumberX;  // number of tiles in the center of screen
		int centralX = lastPos.x() - tilesNumberX / 2;     // position in central coordinates
		if (centralWidth < 1) centralWidth = 1;
		hSB->setSliderPosition(hSB->maximum() * centralX / centralWidth);
		
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		int tilesNumberY = vSB->pageStep() / maxZoom;
		int centralHeight = mapInfo->height - tilesNumberY;
		int centralY = lastPos.y() - tilesNumberY / 2;
		if (centralHeight < 1) centralHeight = 1;
		vSB->setSliderPosition(vSB->maximum() * centralY / centralHeight);
	}
	
	void mouseMoveEvent(QMouseEvent* event) override
	{
		if (!mapInfo) return;
		
		const QPoint& point = event->pos();
		if (!this->rect().contains(point)) return;
		
		// Move sliders
		if (event->buttons() & Qt::RightButton)
		{
			globalPos = event->globalPos();
			
			QScrollBar* hSB = scrollArea->horizontalScrollBar();
			hSB->setSliderPosition(hSB->sliderPosition() - globalPos.x() + lastGlobalPos.x());
			QScrollBar* vSB = scrollArea->verticalScrollBar();
			vSB->setSliderPosition(vSB->sliderPosition() - globalPos.y() + lastGlobalPos.y());
			
			lastGlobalPos = globalPos;
		}
		
		QPoint pos(point.x() / tileLen, point.y() / tileLen);
		rectBase = QRect(pos.x() * tileLenBase, pos.y() * tileLenBase, tileLenBase, tileLenBase);
		
		// Draw objects, if LMB and current item is valid.
		if (tool && (event->buttons() & Qt::LeftButton))
		{
			isHighlight = false;
			
			auto& tile = mapInfo->tiles[pos.y()][pos.x()]; // On map
			if (tool && tool->type == ToolType::TERRAIN)
			{
				ReplaceObject(*groundPixmap, rectBase, tool, tile.terrain);
			}
			else
			{
				// delete, if tool == null
				ReplaceObject(*frontPixmap, rectBase, tool, tile.object);
			}
		}
		else // Highlight current rectangle
		{
			isHighlight = true;
		}
		
		// Update rects
		QRect newRectScaled = QRect(pos.x() * tileLen, pos.y() * tileLen, tileLen, tileLen);
		if (lastPos != pos)
		{
			update(rectScaled);
			update(newRectScaled);
			rectScaled = newRectScaled;
			lastPos = pos;
		}
	}
	
	void mousePressEvent(QMouseEvent* event) override
	{
		lastGlobalPos = event->globalPos();
		if (event->buttons() & Qt::RightButton)
		{
			grabMouse(QCursor(Qt::ClosedHandCursor));
		}
		else
		{
			grabMouse();
		}
		
		mouseMoveEvent(event); // for single mouse click processing
	}
	
	void mouseReleaseEvent(QMouseEvent* event) override
	{
		Q_UNUSED(event);
		
		releaseMouse();
	}

private:
	void ReplaceObject(QPixmap& pixmap, const QRect& rc, ToolInfo* object, ToolInfo*& currentObject)
	{
		if (currentObject == object) return;
		
		currentObject = object;
		{
			QPainter painter(&pixmap);
			painter.setCompositionMode(QPainter::CompositionMode_Source);
			if (object)
				painter.drawPixmap(rc, object->image);
			else
				painter.fillRect(rc, QColor(0, 0, 0, 0));
		}
		update(rc);
		
		emit MapChanged();
	}
	
	void SetMap(MapInfo* mapInfo)
	{
		this->mapInfo.reset(mapInfo);
		size_t width = mapInfo->width;
		size_t height = mapInfo->height;
		QSize groundSize((int) width * tileLenBase, (int) height * tileLenBase);
		
		groundPixmap.reset(new QPixmap(groundSize));
		frontPixmap.reset(new QPixmap(groundSize));
		frontPixmap->fill(QColor(0, 0, 0, 0)); // Necessary clear!
		
		// Draw ground and objects
		QPainter groundPainter, frontPainter;
		groundPainter.begin(groundPixmap.get());
		frontPainter.begin(frontPixmap.get());
		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				const QRect& rc = QRect(col * tileLenBase, row * tileLenBase, tileLenBase, tileLenBase);
				auto&& tile = mapInfo->tiles[row][col];
				groundPainter.drawPixmap(rc, tile.terrain->image);
				if (tile.object)
				{
					frontPainter.drawPixmap(rc, tile.object->image);
				}
			}
		}
		groundPainter.end();
		frontPainter.end();
		
		tileLen = tileLenBase / 2;
		setFixedSize(groundSize * tileLen / tileLenBase);
		update();
	}
	
	void CurrentToolChanged(ToolInfo* tool)
	{
		this->tool = tool;
	}

signals:
	void MapChanged(bool yes = true);
};
#include "MapAreaWidget.moc"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MapAreaWidget::MapAreaWidget(QWidget* parent)
		: QScrollArea(parent)
		, impl(new MapAreaWidgetImpl(this))
{
	setWidget(impl);
	setAlignment(Qt::AlignCenter);
	
	connect(impl, &MapAreaWidgetImpl::MapChanged, this, &MapChanged);
}

MapAreaWidget::~MapAreaWidget() = default;

const QString& MapAreaWidget::GetMapName() const
{
	return impl->mapInfo->name;
}

void MapAreaWidget::SetMap(const QString& name, size_t width, size_t height)
{
	impl->SetMap(new MapInfo(name, width, height));
}

void MapAreaWidget::LoadFromFile(const QString& fileName)
{
	impl->SetMap(new MapInfo(fileName));
}

bool MapAreaWidget::SaveToFile(const QString& fileName) const
{
	impl->mapInfo->SaveToFile(fileName);
}

void MapAreaWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}

void MapAreaWidget::CurrentToolChanged(ToolInfo* tool)
{
	impl->CurrentToolChanged(tool);
}

}