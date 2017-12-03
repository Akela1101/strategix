#ifndef _GameWidget_H
#define _GameWidget_H

#include <nya.hpp>
#include <Strategix_Forward.h>
#include <MapInfo_Forward.h>
#include <QScrollArea>


class QWheelEvent;

namespace map_info
{
class GameWidget : public QScrollArea
{
Q_OBJECT
	MapWidget* impl;

public:
	GameWidget(QWidget* parent = nullptr);
	~GameWidget() override;
	
	void SetMap(strx::Map* map);

protected:
	virtual MapWidget* CreateMapWidget() = 0;
	
	void wheelEvent(QWheelEvent* event);

public slots:
	void CurrentToolChanged(ToolInfo* tool);
	void CurrentPlayerChanged(int playerNumber);

signals:
	void MapChanged(bool yes);
};

}

#endif //_GameWidget_H

