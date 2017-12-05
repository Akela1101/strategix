#ifndef _EditorGameWidget_H
#define _EditorGameWidget_H

#include <GameWidget.h>

namespace map_editor
{
using namespace map_info;

class EditorGameWidget : public GameWidget
{
Q_OBJECT
	using GameWidget::GameWidget;
	
	MapWidget* CreateMapWidget() override;

public slots:
	void CurrentToolChanged(ToolInfo* tool);
	void CurrentPlayerChanged(int playerId);
};
}

#endif //_EditorGameWidget_H
