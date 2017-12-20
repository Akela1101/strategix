#pragma once

#include <Sample_Forward.h>
#include <GameWidget.h>

class QWidget;
class QLabel;

namespace sample1
{
class SampleGameWidget : public map_info::GameWidget
{
Q_OBJECT
	QWidget* resourcesWidget;
	umap<string, QLabel*> resourceAmountLabels;

public:
	SampleGameWidget();

public slots:
	void OnResourcesChanged(Resources newResources);
};
}
