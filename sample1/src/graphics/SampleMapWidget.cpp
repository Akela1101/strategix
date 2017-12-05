#include <strx/map/MapObject.h>
#include <MapInfo.h>
#include <QtGui>

#include "SampleMapWidget.h"


namespace sample1
{
SampleMapWidget::SampleMapWidget(QScrollArea* parent) 
		: MapWidget(parent)
{}

void SampleMapWidget::paintEvent(QPaintEvent* event)
{
	MapWidget::paintEvent(event);
}

void SampleMapWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		//grabMouse();
	}
	MapWidget::mousePressEvent(event);
}

}
