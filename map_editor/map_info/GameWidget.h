#pragma once

#include <nya.hpp>
#include <Strategix_fwd.h>
#include <MapInfo_fwd.h>
#include <QScrollArea>


class QWheelEvent;

namespace map_info
{
class GameWidget : public QScrollArea
{
public:
	GameWidget(QWidget* parent = nullptr);
	~GameWidget() override;
	
	template<typename T> T* CreateMapWidget()
	{
		auto mapWidget = new T(this);
		setWidget(mapWidget);
		return mapWidget;
	}

protected:
	void wheelEvent(QWheelEvent* event);
};

}
