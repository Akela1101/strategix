#ifndef _EditorMapWidget_H
#define _EditorMapWidget_H

#include <MapWidget.h>


namespace map_editor
{
using namespace map_info;

class EditorMapWidget : public MapWidget
{
	using MapWidget::MapWidget;
	
	bool isHighlight = false;     // highlight cell under cursor
	QRect lastRc;                 // last rect under cursor

protected:
	void paintEvent(QPaintEvent*) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	
private:
	static QRect GetBaseRect(QPoint pos);
	void UpdateUnderMouse(QMouseEvent* event);
};
}

#endif //_EditorMapWidget_H
