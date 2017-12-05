#ifndef _SampleMapWidget_H
#define _SampleMapWidget_H

#include <MapWidget.h>


namespace sample1
{
class SampleMapWidget : public map_info::MapWidget
{
public:
	SampleMapWidget(QScrollArea* parent);

protected:
	void paintEvent(QPaintEvent*) override;
	void mousePressEvent(QMouseEvent* event) override;
	
};
}

#endif //_SampleMapWidget_H
