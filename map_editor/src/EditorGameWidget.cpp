#include <EditorMapWidget.h>

#include "EditorGameWidget.h"


namespace map_editor
{
MapWidget* EditorGameWidget::CreateMapWidget()
{
	return new EditorMapWidget(this);
}

void EditorGameWidget::CurrentToolChanged(ToolInfo* tool)
{
	((EditorMapWidget*) impl)->tool = tool;
}

void EditorGameWidget::CurrentPlayerChanged(int playerId)
{
	((EditorMapWidget*) impl)->playerId = playerId;
}

}

