#include <EditorMapWidget.h>

#include "EditorGameWidget.h"


namespace map_editor
{
MapWidget* EditorGameWidget::CreateMapWidget()
{
	return new EditorMapWidget(this);
}
}

