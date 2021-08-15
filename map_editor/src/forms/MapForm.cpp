#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardPaths>
#include <boost/filesystem.hpp>
#include <fstream>
#include <nya/io.hpp>

#include <EditorMapWidget.hpp>
#include <MapInfo.hpp>
#include <strx/Map.hpp>


#include "DialogNew.hpp"
#include "MapForm.hpp"


namespace map_editor
{
using namespace map_info;

static const char editorTitle[] = "Strategix Map Editor";

static const char* str(const QString& message)
{
	return message.toUtf8().data();
}


MapForm::MapForm() : isMapOpened(false)
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
	ListWidgetFill(ToolType::ENTITY, "az_base", widget.toolsListWidget);
	ListWidgetFill(ToolType::ENTITY, "az_worker", widget.toolsListWidget);

	// set current tool to delete object
	widget.toolBox->setCurrentIndex(1);
	widget.toolsListWidget->setCurrentRow(0);

	//
	mapWidget = widget.gameWidget->CreateMapWidget<EditorMapWidget>();
	connect(this, &MapForm::CurrentToolChanged, mapWidget, &EditorMapWidget::CurrentToolChanged);
	connect(this, &MapForm::CurrentPlayerChanged, mapWidget, &EditorMapWidget::CurrentPlayerChanged);
	connect(mapWidget, &EditorMapWidget::MapChanged, this, &MapForm::MapChanged);
}

MapForm::~MapForm() = default;

void MapForm::FileNew()
{
	if (!TrySaveMap()) return;

	DialogNew dialogNew;
	if (dialogNew.exec() == QDialog::Accepted)
	{
		QString name = dialogNew.mapName;
		try
		{
			map.reset(new Map(name.toStdString(), dialogNew.mapWidth, dialogNew.mapHeight, MapInfo::terrains));
			mapWidget->SetMap(map);
		}
		catch (exception& e)
		{
			QMessageBox::critical(nullptr, QString("Error creating map: %1").arg(name), e.what());
		}
		isMapOpened = true;
		MapChanged();
	}
}

void MapForm::FileSave()
{
	SaveMap();
}

void MapForm::FileLoad()
{
	using path = boost::filesystem::path;

	if (!TrySaveMap()) return;

	// load location
	string configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString();
	string lastLocationPath = (path(configPath) / "last_path.conf").string();
	string lastPath;
	ifstream fin(lastLocationPath);
	if (fin) nya_getline(fin, lastPath);

	fin.close();

	// open file
	QString loadedMapPath = QFileDialog::getOpenFileName(this, "Load the map", lastPath.c_str(), "Maps (*.map)");
	if (loadedMapPath.isEmpty()) return;

	mapPath = loadedMapPath;
	try
	{
		map.reset(new Map(mapPath.toStdString()));
		map->UpdateTerrains(MapInfo::terrains);
		mapWidget->SetMap(map);
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
	if (fout) fout << mapPath.toStdString();
}

void MapForm::FileExit()
{
	// Setted to close() by Designer
	// Change it. And ask for save, if not saved
}

void MapForm::HelpAbout()
{
	QMessageBox::about(this, editorTitle,
	        QString("Version: %1 \n(C) 2010-%2 %3").arg(mapFormatVersion).arg(__DATE__ + 7).arg("Akela1101"));
}

void MapForm::CurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
	Q_UNUSED(previous);

	if (current)
		this->statusBar()->showMessage(current->text());
	else
		this->statusBar()->showMessage("***");

	emit CurrentToolChanged(toolFromItem[current]);
}

void MapForm::CurrentToolboxItemChanged(int index)
{
	if (auto listWidget = dynamic_cast<QListWidget*>(widget.toolBox->widget(index)->children().last()))
	{
		CurrentItemChanged(listWidget->currentItem(), nullptr);
	}
}

void MapForm::PlayerButtonToggled(bool on)
{
	int playerNumber = playerNumbers[(QPushButton*) sender()];
	emit CurrentPlayerChanged(playerNumber);
}

void MapForm::PlacePlayerMarks()
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
		connect(button, &QPushButton::toggled, this, &MapForm::PlayerButtonToggled);
	}
	widget.playersGroupBox->setLayout(layout);
}

void MapForm::ListWidgetFillMark(const string& filePath, QListWidget* listWidget)
{
	using path = boost::filesystem::path;

	string name = path(filePath).stem().string();
	QPixmap pixmap = MapInfo::LoadPixmap(filePath);

	QListWidgetItem* newItem = AddToListWidget(name, pixmap, listWidget);
	toolFromItem.emplace(newItem, nullptr);
}

void MapForm::ListWidgetFill(ToolType type, const std::string& name, QListWidget* listWidget)
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
		case ToolType::ENTITY:
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

QListWidgetItem* MapForm::AddToListWidget(const string& name, const QPixmap& pixmap, QListWidget* listWidget)
{
	QString title = QString(name.c_str()).replace('_', ' ');
	QListWidgetItem* newItem = new QListWidgetItem(QIcon(pixmap), title);
	listWidget->addItem(newItem);
	return newItem;
}

bool MapForm::TrySaveMap()
{
	// Trying to save previous opened map
	if (isMapOpened && !isMapSaved)
	{
		if (QMessageBox::Yes
		        == QMessageBox::question(this, "Map wasn't saved", "Save changes?", QMessageBox::Yes | QMessageBox::No,
		                QMessageBox::No))
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
	mapPath.clear();  // !!! allow open save dialog for new map
	return true;
}

QString MapForm::SaveMap()
{
	if (mapPath.isEmpty())
	{
		QString fileNameHint = map->GetName().c_str();
		mapPath = QFileDialog::getSaveFileName(this, "Save the map", fileNameHint, "Maps (*.map)");

		statusBar()->showMessage(mapPath, 3000);

		// if user reconsider saving
		if (mapPath.isEmpty()) return mapPath;
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

void MapForm::MapChanged(bool yes)
{
	isMapSaved = !yes;
	widget.actionSave->setEnabled(yes);
	QString mapName = map->GetName().c_str();
	setWindowTitle(QString("%1 %2- %3").arg(mapName).arg(yes ? "(*) " : "").arg(editorTitle));
}

}  // namespace map_editor
