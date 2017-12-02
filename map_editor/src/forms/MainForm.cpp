#include <fstream>
#include <boost/filesystem.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QPushButton>
#include <MapInfo.h>
#include <strx/map/BaseMap.h>

#include "DialogNew.h"
#include "MainForm.h"


namespace map_editor
{
using namespace strx;
using namespace map_info;

static const char editorTitle[] = "Strategix Map Editor";

static const char* str(const QString& message) { return message.toUtf8().data(); }


MainForm::MainForm()
		: isMapOpened(false)
{
	widget.setupUi(this);
	
	setWindowTitle(editorTitle);
	widget.actionSave->setEnabled(false);
	
	MapInfo::LoadTerrainTools();
	MapInfo::LoadObjectTools();
	
	// player marks
	PlacePlayerMarks();
	
	// terrains
	for (auto&& name_info : MapInfo::terrainTools)
	{
		ListWidgetFill(ToolType::TERRAIN, name_info.first, widget.terrainListWidget);
	}
	
	// tools
	ListWidgetFillMark("config/images/delete_object.png", widget.toolsListWidget);
	
	// resources
	ListWidgetFill(ToolType::MINE, "gold", widget.toolsListWidget);
	ListWidgetFill(ToolType::MINE, "tree", widget.toolsListWidget);
	
	// objects
	ListWidgetFill(ToolType::OBJECT, "az_base", widget.toolsListWidget);
	ListWidgetFill(ToolType::OBJECT, "az_worker", widget.toolsListWidget);
	
	// set current tool to delete object
	widget.toolBox->setCurrentIndex(1);
	widget.toolsListWidget->setCurrentRow(0);
	
	//
	connect(this, &CurrentToolChanged, widget.mapArea, &MapAreaWidget::CurrentToolChanged);
	connect(this, &CurrentPlayerChanged, widget.mapArea, &MapAreaWidget::CurrentPlayerChanged);
	connect(widget.mapArea, &MapAreaWidget::MapChanged, this, &MapChanged);
}

MainForm::~MainForm() = default;

void MainForm::FileNew()
{
	if (!TrySaveMap())
		return;
	
	DialogNew dialogNew;
	if (dialogNew.exec() == QDialog::Accepted)
	{
		QString name = dialogNew.mapName;
		try
		{
			map.reset(new BaseMap(name.toStdString(), dialogNew.mapWidth, dialogNew.mapHeight));
			widget.mapArea->SetMap(map.get());
		}
		catch (exception& e)
		{
			QMessageBox::critical(nullptr, QString("Error creating map: %1").arg(name), e.what());
		}
		isMapOpened = true;
		MapChanged();
	}
}

void MainForm::FileSave()
{
	SaveMap();
}

void MainForm::FileLoad()
{
	using path = boost::filesystem::path;
	
	if (!TrySaveMap()) return;
	
	// load location
	string configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString();
	string lastLocationPath = (path(configPath) / "last_path.conf").string();
	string lastPath;
	ifstream fin(lastLocationPath);
	if (fin)
		getline(fin, lastPath);
	
	fin.close();
	
	// open file
	QString loadedMapPath = QFileDialog::getOpenFileName(this, "Load the map", lastPath.c_str(), "Maps (*.map)");
	if (loadedMapPath.isEmpty()) return;
	
	mapPath = loadedMapPath;
	try
	{
		map.reset(new BaseMap(mapPath.toStdString()));
		widget.mapArea->SetMap(map.get());
	}
	catch (exception& e)
	{
		QMessageBox::critical(nullptr, QString("Error while reading the file: %1").arg(mapPath), e.what());
		return;
	}
	isMapOpened = true;
	MapChanged(false);
	
	// save location
	boost::filesystem::create_directories(configPath);
	ofstream fout(lastLocationPath, ios::trunc);
	if (fout)
		fout << mapPath.toStdString();
}

void MainForm::FileExit()
{
	// Setted to close() by Designer
	// Change it. And ask for save, if not saved
}

void MainForm::HelpAbout()
{
	QMessageBox::about(this, editorTitle, QString("Version: %1 \n(C) 2010-%2 %3")
			.arg(mapFormatVersion)
			.arg(__DATE__ + 7)
			.arg("Akela1101"));
}

void MainForm::CurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
	Q_UNUSED(previous);
	
	if (current)
		this->statusBar()->showMessage(current->text());
	else
		this->statusBar()->showMessage("***");
	
	emit CurrentToolChanged(toolFromItem[current]);
}

void MainForm::CurrentToolboxItemChanged(int index)
{
	if (auto listWidget = dynamic_cast<QListWidget*>(widget.toolBox->widget(index)->children().last()))
	{
		CurrentItemChanged(listWidget->currentItem(), nullptr);
	}
}

void MainForm::PlayerButtonToggled(bool on)
{
	int playerNumber = playerNumbers[(QPushButton*)sender()];
	emit CurrentPlayerChanged(playerNumber);
}

void MainForm::PlacePlayerMarks()
{
	auto layout = new QHBoxLayout();
	layout->setMargin(0);
	
	QPushButton* firstButton = nullptr;
	int i = 0;
	for (auto&& playerMark : MapInfo::playerMarks)
	{
		auto button = new QPushButton();
		button->setIcon(QIcon(playerMark));
		button->setCheckable(true);
		button->setAutoExclusive(true);
		button->setFlat(true);
		
		layout->addWidget(button);
		if (!firstButton)
		{
			firstButton = button;
			button->setChecked(true);
		}
		playerNumbers.emplace(button, i++);
		connect(button, &QPushButton::toggled, this, &PlayerButtonToggled);
	}
	widget.playersGroupBox->setLayout(layout);
}

void MainForm::ListWidgetFillMark(const string& filePath, QListWidget* listWidget)
{
	using path = boost::filesystem::path;
	
	string name = path(filePath).stem().string();
	QPixmap pixmap = MapInfo::LoadPixmap(filePath);
	
	QListWidgetItem* newItem = AddToListWidget(name, pixmap, listWidget);
	toolFromItem.emplace(newItem, nullptr);
}

void MainForm::ListWidgetFill(ToolType type, const std::string& name, QListWidget* listWidget)
{
	ToolInfo* tool = nullptr;
	switch (type)
	{
		case ToolType::TERRAIN:
		{
			tool = &MapInfo::terrainTools[name];
			break;
		}
		case ToolType::MINE:
		case ToolType::OBJECT:
		{
			tool = &MapInfo::objectTools[name];
			break;
		}
		default:
		{
			error_log << "Unable to handle %s tool"s % type.c_str();
			return;
		}
	}
	
	QListWidgetItem* newItem = AddToListWidget(name, tool->image, listWidget);
	toolFromItem.emplace(newItem, tool);
}

QListWidgetItem* MainForm::AddToListWidget(const string& name, const QPixmap& pixmap, QListWidget* listWidget)
{
	QString title = QString(name.c_str()).replace('_', ' ');
	QListWidgetItem* newItem = new QListWidgetItem(QIcon(pixmap), title);
	listWidget->addItem(newItem);
	return newItem;
}

bool MainForm::TrySaveMap()
{
	// Trying to save previous opened map
	if (isMapOpened && !isMapSaved)
	{
		if (QMessageBox::Yes ==
				QMessageBox::question(this, "Map wasn't saved", "Save changes?", QMessageBox::Yes | QMessageBox::No
						, QMessageBox::No))
		{
			if (SaveMap().isEmpty())
			{
				// user pressed X or cancel
				return false;
			}
			// else saving successful, able to continue
		}
		// else user don't want to save map
	}
	mapPath.clear(); // !!! allow open save dialog for new map
	return true;
}

QString MainForm::SaveMap()
{
	if (mapPath.isEmpty())
	{
		QString fileNameHint = map->GetName().c_str();
		mapPath = QFileDialog::getSaveFileName(this, "Save the map", fileNameHint, "Maps (*.map)");
		
		statusBar()->showMessage(mapPath, 3000);
		
		// if user reconsider saving
		if (mapPath.isEmpty())
			return mapPath;
	}
	// Write file
	try
	{
		map->SaveToFile(mapPath.toStdString());
		MapChanged(false);
	}
	catch (exception& ex)
	{
		mapPath.clear();
		QMessageBox::critical(this, "Unable to save map", ex.what());
	}
	return mapPath;
}

void MainForm::MapChanged(bool yes)
{
	isMapSaved = !yes;
	widget.actionSave->setEnabled(yes);
	QString mapName = map->GetName().c_str();
	setWindowTitle(QString("%1 %2- %3")
			.arg(mapName)
			.arg(yes ? "(*) " : "")
			.arg(editorTitle));
}

}