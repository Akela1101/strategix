#ifndef _MAPAREA_H
#define    _MAPAREA_H

#include <nya.hpp>
#include <Strategix_Forward.h>
#include <QScrollArea>


class QWheelEvent;

namespace map_info
{
class MapInfo;
class MapAreaWidgetImpl;
class ToolInfo;

class MapAreaWidget : public QScrollArea
{
Q_OBJECT
	MapAreaWidgetImpl* impl;

public:
	MapAreaWidget(QWidget* parent = nullptr);
	~MapAreaWidget() override;
	
	void SetMap(strx::Map* map);

protected:
	void wheelEvent(QWheelEvent* event);

public slots:
	void CurrentToolChanged(ToolInfo* tool);
	void CurrentPlayerChanged(int playerNumber);

signals:
	void MapChanged(bool yes);
};
}

#endif    /* _MAPAREA_H */

