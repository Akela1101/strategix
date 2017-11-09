#include "MapArea.h"
#include "MainForm.h"

#include <QScrollBar>


static QPoint globalPoint, lastGlobalPoint;

MapArea::MapArea(QWidget* parent) : QWidget(parent)
{
	tileSize = 50;
	this->setMouseTracking(true);
	isHighlight = false;
}

void MapArea::SetPs(MainForm* mainForm, QScrollArea* scrollArea)
{
	this->mainForm = mainForm;
	this->scrollArea = scrollArea;
}

void MapArea::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	
	if (!mapInfo)
		return;
	
	QPainter painter(this);
	painter.drawPixmap(0, 0, *groundPixmap);
	painter.drawPixmap(0, 0, *frontPixmap);
	
	if (isHighlight)
	{
		painter.setBrush(QColor(250, 250, 100, 150));
		painter.setPen(Qt::NoPen);
		painter.drawRect(lastRc);
	}
}

void MapArea::mouseMoveEvent(QMouseEvent* event)
{
	const QPoint& point = event->pos();
	
	if (!mapInfo || !this->rect().contains(point))
		return;
	
	// Move sliders
	if (event->buttons() & Qt::RightButton)
	{
		globalPoint = event->globalPos();
		
		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		hSB->setSliderPosition(hSB->sliderPosition() - globalPoint.x() + lastGlobalPoint.x());
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		vSB->setSliderPosition(vSB->sliderPosition() - globalPoint.y() + lastGlobalPoint.y());
		
		lastGlobalPoint = globalPoint;
	}
	
	const int tileX = point.x() / tileSize;
	const int tileY = point.y() / tileSize;
	const QRect& rc = QRect(tileX * tileSize, tileY * tileSize, tileSize, tileSize);
	
	// Draw objects, if LMB and current item is valid.
	if ((event->buttons() & Qt::LeftButton) && (mainForm->currentItem))
	{
		isHighlight = false;
		
		MapInfo::Tile& tile = mapInfo->tiles[tileY][tileX]; // On map
		const s_p<ObjectInfo> newObj = objectFromItem[mainForm->currentItem]; // In mouse
		
		// *** currentItem is only from currentToolboxIndex ***
		
		switch (mainForm->currentToolboxIndex)
		{
			case 0: // Tools
			{
				s_p<ObjectInfo>& obj = tile.object;
				if (obj != newObj)
				{
					AddObjectWithPainter(frontPixmap, rc, obj, newObj);
				}
				break;
			}
			case 1: // Terrain changing
			{
				s_p<ObjectInfo>& terr = tile.terrain;
				if (terr != newObj)
				{
					AddObjectWithPainter(groundPixmap, rc, terr, newObj);
				}
				break;
			}
			case 2: // Resource add
			{
				s_p<ObjectInfo>& obj = tile.object;
				if (obj != newObj)
				{
					AddObjectWithPainter(frontPixmap, rc, obj, newObj);
				}
				break;
			}
			default:
				; // error
		}
	}
	else // Highlight current rectangle
	{
		isHighlight = true;
	}
	
	// Update rects
	if (lastRc.topLeft() != rc.topLeft())
	{
		this->update(lastRc);
		lastRc = rc;
		this->update(lastRc);
	}
}

void MapArea::AddObjectWithPainter(s_p<QPixmap>& pixmap, const QRect& rc, s_p<ObjectInfo>& obj
		, const s_p<ObjectInfo>& newObj)
{
	obj = newObj;
	{
		QPainter painter(pixmap.get());
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		if (obj)
			painter.drawPixmap(rc, obj->image);
		else
			painter.fillRect(rc, QColor(0, 0, 0, 0));
	}
	this->update(rc);
	
	mainForm->MapChanged(); // !!!
}

void MapArea::mousePressEvent(QMouseEvent* event)
{
	lastGlobalPoint = event->globalPos();
	if (event->buttons() & Qt::RightButton)
	{
		this->grabMouse(QCursor(Qt::ClosedHandCursor));
	}
	else
	{
		this->grabMouse();
	}
	
	this->mouseMoveEvent(event); // for single mouse click processing
}

void MapArea::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	
	this->releaseMouse();
}

//=================================================================

void MapArea::SetMap(s_p<MapInfo>& mapInfo)
{
	this->mapInfo = mapInfo;
	const size_t& width = mapInfo->width;
	const size_t& height = mapInfo->height;
	const QSize groundSize = QSize((int)width * tileSize, (int)height * tileSize);
	
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
			const QRect& rc = QRect(col * tileSize, row * tileSize, tileSize, tileSize);
			const MapInfo::Tile& tile = mapInfo->tiles[row][col];
			groundPainter.drawPixmap(rc, tile.terrain->image);
			if (tile.object)
			{
				frontPainter.drawPixmap(rc, tile.object->image);
			}
		}
	}
	groundPainter.end();
	frontPainter.end();
	
	this->setFixedSize(groundSize);
	this->update();
}

s_p<MapInfo> MapArea::GetMapInfo() const
{
	return mapInfo;
}
