#include <MapWidget.h>
#include <QWheelEvent>

#include "GameWidget.h"


namespace map_info
{
GameWidget::GameWidget(QWidget* parent)
		: QScrollArea(parent)
{
	setAlignment(Qt::AlignCenter);
}

GameWidget::~GameWidget() = default;

void GameWidget::SetMap(Map* map)
{
	setWidget(impl = CreateMapWidget());
	impl->SetMap(map);
	
	connect(impl, &MapWidget::MapChanged, this, &MapChanged);
}

void GameWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}

}