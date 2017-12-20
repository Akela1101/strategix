#pragma once

#include <nya.hpp>
#include <Strategix_Forward.h>
#include <MapInfo_Forward.h>
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
