#include <MapInfo.h>
#include <strx/common/Resources.h>
#include <strx/kernel/Kernel.h>
#include <graphics/SampleMapWidget.h>
#include <QLabel>
#include <QHBoxLayout>

#include "SampleGameWidget.h"


namespace sample1
{
using namespace map_info;

static const int len = 32;

SampleGameWidget::SampleGameWidget()
		: GameWidget()
		, resourcesWidget(new QWidget(this))
{
	resize(1200, 600);
	resourcesWidget->setMaximumHeight(len + 4);
	resourcesWidget->setContentsMargins(8, 2, 8, 2);
	resourcesWidget->setStyleSheet(".QWidget { background-color : rgba(100, 100, 100, 0.3) }");
	
	auto layout = new QHBoxLayout();
	layout->setMargin(0);
	for (auto&& resourceInfo : Kernel::GetResourceInfos())
	{
		auto imageLabel = new QLabel();
		imageLabel->setFixedSize(len, len);
		imageLabel->setScaledContents(true);
		imageLabel->setPixmap(MapInfo::objectTools[resourceInfo].image);
		layout->addWidget(imageLabel);
		
		auto amountLabel = new QLabel("0");
		amountLabel->setStyleSheet("color : white; font-weight: bold");
		layout->addWidget(amountLabel);
		
		resourceAmountLabels.emplace(resourceInfo, amountLabel);
	}
	resourcesWidget->setLayout(layout);
}

void SampleGameWidget::OnResourcesChanged(Resources newResources)
{
	for (auto&& resource : newResources)
	{
		resourceAmountLabels[resource.first]->setText(QString::number(resource.second));
	}
	resourcesWidget->adjustSize();
}

}
