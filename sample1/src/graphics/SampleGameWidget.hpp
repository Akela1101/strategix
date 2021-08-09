#pragma once

#include <GameWidget.hpp>
#include <Sample_fwd.hpp>

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
	SampleGameWidget(const ResourceInfosType& resourceInfos);

public slots:
	void OnResourcesChanged(Resources newResources);
};
}  // namespace sample1
