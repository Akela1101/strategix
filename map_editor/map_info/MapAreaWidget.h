#ifndef _MAPAREA_H
#define    _MAPAREA_H

#include <QScrollArea>
#include <nya.hpp>


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
	
	const QString& GetMapName() const;
	void SetMap(const QString& name, size_t width, size_t height);
	void LoadFromFile(const QString& fileName);
	bool SaveToFile(const QString& fileName) const;

protected:
	void wheelEvent(QWheelEvent* event);

public slots:
	void CurrentToolChanged(ToolInfo* tool);

signals:
	void MapChanged(bool yes);
};
}

#endif    /* _MAPAREA_H */

