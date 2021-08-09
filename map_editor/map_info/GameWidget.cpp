#include <QWheelEvent>

#include "MapWidget.hpp"

#include "GameWidget.hpp"


namespace map_info
{
GameWidget::GameWidget(QWidget* parent) : QScrollArea(parent)
{
	setAlignment(Qt::AlignCenter);
}

GameWidget::~GameWidget() = default;

void GameWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}

}  // namespace map_info