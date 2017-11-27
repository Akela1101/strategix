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
	
	QScrollArea* scrollArea;      // back link to scroll area
	ToolInfo* tool = nullptr;     // current tool
	int playerNumber = 0;         // current player
	int tileLen = 0;              // tile width | height
	bool isHighlight = false;     // highlight tile under cursor
	
	u_p<MapInfo> mapInfo;         // map related operations
	u_p<QPixmap> groundPixmap;    // terrain pixmap
	u_p<QPixmap> frontPixmap;     // objects pixmap
	
	QRect rectBase;
	QRect rectScaled;
	QPoint lastPos;
	QPoint globalPos;
	QPoint lastGlobalPos;

public:
	MapAreaWidgetImpl(QScrollArea* parent)
			: QWidget(parent)
			, scrollArea(parent)
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
		if (event->buttons() & Qt::LeftButton)
		{
			isHighlight = false;
			
			auto& tile = mapInfo->tiles[pos.y()][pos.x()];
			if (tool && tool->type == ToolType::TERRAIN)
			{
				if (tile.terrain != tool)
				{
					tile.terrain = tool;
					DrawTerrain(tool, rectBase, tile);
				}
			}
			else
			{
				MapInfo::Object* object = CreateObject();
				tile.object.reset(object);
				DrawObject(object, rectBase, tile);
			}
			update(rectBase);
			emit MapChanged();
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
	
	void mouseReleaseEvent(QMouseEvent*) override
	{
		releaseMouse();
	}

private:
	void DrawTerrain(ToolInfo* tool, const QRect& rc, MapInfo::Tile& tile)
	{
		QPainter painter(groundPixmap.get());
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.drawPixmap(rc, tool->image);
	}
	
	void DrawObject(MapInfo::Object* object, const QRect& rc, MapInfo::Tile& tile)
	{
		QPainter painter(frontPixmap.get());
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		if (!object)
		{
			painter.fillRect(rc, QColor(0, 0, 0, 0));
			return;
		}
		
		painter.drawPixmap(rc, object->info.image);
		if (object->info.type == ToolType::OBJECT)
		{
			auto playerObject = (MapInfo::PlayerObject*)object;
			int w = rc.width(), h = rc.height();
			QRect markRc = rc.adjusted(0, 0, -w / 2, -h / 2);
			
			painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
			painter.drawPixmap(markRc, MapInfo::GetPlayerMark(playerObject->owner));
		}
	}
	
	MapInfo::Object* CreateObject()
	{
		if (!tool) return nullptr;
		
		switch (tool->type)
		{
			case ToolType::OBJECT:
				return new MapInfo::PlayerObject{ *tool, playerNumber };
			case ToolType::MINE:
				return new MapInfo::MineObject{ *tool, 1000 };
		}
		return nullptr;
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
		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				const QRect& rc = QRect(col * tileLenBase, row * tileLenBase, tileLenBase, tileLenBase);
				auto&& tile = mapInfo->tiles[row][col];
				
				DrawTerrain(tile.terrain, rc, tile);
				DrawObject(tile.object.get(), rc, tile);
			}
		}
		
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

QString MapAreaWidget::GetMapName() const
{
	return impl->mapInfo ? impl->mapInfo->name : "";
}

void MapAreaWidget::SetMap(const QString& name, size_t width, size_t height)
{
	impl->SetMap(new MapInfo(name, width, height));
}

void MapAreaWidget::LoadFromFile(const QString& fileName)
{
	impl->SetMap(new MapInfo(fileName));
}

void MapAreaWidget::SaveToFile(const QString& fileName) const
{
	if (impl->mapInfo) impl->mapInfo->SaveToFile(fileName);
}

void MapAreaWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}

void MapAreaWidget::CurrentToolChanged(ToolInfo* tool)
{
	impl->CurrentToolChanged(tool);
}

void MapAreaWidget::CurrentPlayerChanged(int playerNumber)
{
	impl->playerNumber = playerNumber;
}

}