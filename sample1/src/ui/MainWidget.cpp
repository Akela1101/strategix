#include <QPushButton>
#include <QStackedWidget>
#include <strx/Message.hpp>
#include <ui_MainWidget.h>

#include "MainWidget.hpp"


namespace sample1
{
MainWidget::MainWidget(QWidget* parent) : QWidget(parent), ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	auto mapsHeaderLabels = QStringList() << "Name"
	                                      << "Players"
	                                      << "Size";
	ui->mapsTableWidget->setColumnCount(mapsHeaderLabels.size());
	ui->mapsTableWidget->setHorizontalHeaderLabels(mapsHeaderLabels);
	auto gamesHeaderLabels = QStringList() << "Map"
	                                       << "Players"
	                                       << "Size"
	                                       << "Host"
	                                       << "Started";
	ui->gamesTableWidget->setColumnCount(gamesHeaderLabels.size());
	ui->gamesTableWidget->setHorizontalHeaderLabels(gamesHeaderLabels);
	ui->listsTabWidget->setCurrentIndex(0);
	ui->joinButton->hide();

	connect(ui->mapsTableWidget, &QTableWidget::cellDoubleClicked, [this](int row, int col) {
		auto mapName = ui->mapsTableWidget->item(row, 0)->text();
		emit CreateGameClicked(mapName);
		ui->listsTabWidget->setCurrentIndex(1);
	});
	connect(ui->gamesTableWidget, &QTableWidget::cellDoubleClicked, [this](int row, int col) {
		auto gameId = ui->gamesTableWidget->item(row, 0)->data(Qt::UserRole).toInt();
		emit GameSelected(gameId);
		ui->joinButton->show();
	});
	connect(ui->joinButton, &QPushButton::clicked, [this]() { emit JoinGameClicked(); });
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::SetMaps(s_p<vector<MapContext>> maps)
{
	ui->mapsTableWidget->clearContents();
	ui->mapsTableWidget->setRowCount(maps->size());
	for (auto row = 0; row < maps->size(); row++)
	{
		ui->mapsTableWidget->setItem(row, 0, new QTableWidgetItem(maps->at(row).name.c_str()));
		ui->mapsTableWidget->setItem(row, 1, new QTableWidgetItem(maps->at(row).playersNumber));
		ui->mapsTableWidget->setItem(row, 2, new QTableWidgetItem(maps->at(row).height <= 32 ? "small" : "medium"));
	}
}

void MainWidget::AddGameContext(const GameMessage* gameMessage)
{
	int row = ui->gamesTableWidget->rowCount();
	ui->gamesTableWidget->setRowCount(row + 1);
	auto firstItem = new QTableWidgetItem(gameMessage->mapName.c_str());
	firstItem->setData(Qt::UserRole, gameMessage->id);
	ui->gamesTableWidget->setItem(row, 0, firstItem);
}

void MainWidget::PrepareGamePage(QWidget* gameWidget)
{
	ui->gamePage->setLayout(new QVBoxLayout);
	ui->gamePage->layout()->addWidget(gameWidget);
}

void MainWidget::StartGamePage()
{
	ui->mainStackedWidget->setCurrentWidget(ui->gamePage);
}
}  // namespace sample1
