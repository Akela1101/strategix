#pragma once

#include <QScrollArea>
#include <nya.hpp>
#include <strx/strx_fwd.hpp>

#include "MapInfo_fwd.hpp"

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

}  // namespace map_info
