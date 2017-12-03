#ifndef _EditorMapWidget_H
#define _EditorMapWidget_H

#include <MapWidget.h>


namespace map_editor
{
using namespace map_info;

class EditorMapWidget : public MapWidget
{
	using MapWidget::MapWidget;

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
};
}

#endif //_EditorMapWidget_H
