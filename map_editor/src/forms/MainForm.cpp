#include <fstream>
#include <boost/range/adaptors.hpp>
#include <boost/range/irange.hpp>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "DialogNew.h"
#include "MainForm.h"


namespace map_editor
{
using namespace map_info;

const char* str(const QString& message) { return message.toUtf8().data(); }


MainForm::MainForm()
		: isMapOpened(false)
{
	widget.setupUi(this);
	
	setWindowTitle(editorTitle);
	widget.actionSave->setEnabled(false);
	
	auto[terrainsImageFileName, divs] = LoadTerrainDescription();
	
	// tools
	ListWidgetFill(ToolType::PLAYER, "Set Player Position", "player_position.png", widget.toolsListWidget);
	ListWidgetFill(ToolType::NONE, "Delete object", "delete_button.png", widget.toolsListWidget);
	
	// terrains
	ListWidgetFillTerrains(terrainsImageFileName, divs);
	
	// resources
	ListWidgetFill(ToolType::MINE, "Gold", "gold.png", widget.resourceListWidget);
	
	//
	connect(this, &CurrentToolChanged, widget.mapArea, &MapAreaWidget::CurrentToolChanged);
	connect(widget.mapArea, &MapAreaWidget::MapChanged, this, &MapChanged);
}

void MainForm::FileNew()
{
	if (!TrySaveMap())
		return;
	
	DialogNew dialogNew;
	if (dialogNew.exec() == QDialog::Accepted)
	{
		widget.mapArea->SetMap(dialogNew.mapName, dialogNew.mapWidth, dialogNew.mapHeight);
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
	if (!TrySaveMap())
		return;
	
	QString loadedFileName = QFileDialog::getOpenFileName(this, "Load the map", "", "Maps (*.map)");
	if (!loadedFileName.isEmpty())
	{
		fileName = loadedFileName;
		widget.mapArea->LoadFromFile(fileName);
		isMapOpened = true;
		MapChanged(false);
	}
}

void MainForm::FileExit()
{
	// Setted to close() by Designer
	// Change it. And ask for save, if not saved
}

void MainForm::HelpAbout()
{
	QMessageBox::about(this, editorTitle, QString("Version: %1 \n(C) 2010-%2 %3")
			.arg(editorVersion)
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
	
	emit CurrentToolChanged(infoFromItem[current]);
}

void MainForm::CurrentToolboxItemChanged(int index)
{
	const QListWidget* listWidget = dynamic_cast<QListWidget*>(widget.toolBox->widget(index)->children().last());
	// ^ Why last - i don't know ^_^
	
	CurrentItemChanged(listWidget->currentItem(), nullptr);
}

//------------------------------------------------------------------------------
std::pair<std::string, int> MainForm::LoadTerrainDescription()
{
	std::string terrainsImageFileName;
	int divs;
	
	QString fileName = QDir(configDir).filePath(terrainsDefinitionFileName);
	ifstream fin(fileName.toLocal8Bit());
	if (!fin.good())
	{
		throw_nya << str(tr("%1 could not be loaded.").arg(fileName));
	}
	
	getline(fin, terrainsImageFileName);
	fin >> divs;
	
	for (int i : boost::irange(0, divs * divs))
	{
		auto info = make_u<TerrainInfo>();
		fin >> info->retard >> info->name;
		if (fin.eof()) break;
		
		info->type = ToolType::TERRAIN;
		info->id = i;
		MapInfo::terrainInfos.emplace(info->name, std::move(info));
	}
	fin.close();
	return { terrainsImageFileName, divs };
}

void MainForm::ListWidgetFillTerrains(const std::string& terrainsImageFileName, int divs)
{
	QPixmap pixmap;
	if (!pixmap.load(QDir(configDir).filePath(terrainsImageFileName.c_str())))
	{
		throw_nya << str(tr("The image files could not be loaded from %1").arg(terrainsImageFileName.c_str()));
	}
	int tileSize = pixmap.width() / divs;
	
	for (int row = 0; row < divs; ++row)
	{
		for (int col = 0; col < divs; ++col)
		{
			TerrainInfo* info = MapInfo::GetTerrainById(divs * row + col);
			if (info->name == "none")
				break; // none name are skipped !!!
			
			const QPixmap& terrPixmap = pixmap.copy(col * tileSize, row * tileSize, tileSize, tileSize);
			
			ListWidgetFill(ToolType::TERRAIN, info->name, terrPixmap, widget.terrainListWidget);
		}
	}
}

void MainForm::ListWidgetFill(ToolType type, const std::string& name
		, const QString& imageFileName, QListWidget* listWidget)
{
	QPixmap pixmap;
	pixmap.load(QDir(imagesPath).filePath(imageFileName));
	ListWidgetFill(type, name, pixmap, listWidget);
}

void MainForm::ListWidgetFill(ToolType type, const std::string& name, const QPixmap& pixmap, QListWidget* listWidget)
{
	// Add List entry
	QListWidgetItem* newItem = new QListWidgetItem(QIcon(pixmap), QString(name.c_str()));
	listWidget->addItem(newItem);
	
	ToolInfo* pInfo = nullptr;
	switch (type)
	{
		case ToolType::PLAYER:
		case ToolType::MINE:
		{
			auto info = make_u<ToolInfo>(type, name, pixmap);
			pInfo = info.get();
			MapInfo::objectInfos.emplace(type, std::move(info));
			break;
		}
		case ToolType::TERRAIN:
		{
			pInfo = MapInfo::terrainInfos[name].get();
			pInfo->image = pixmap;
			break;
		}
	}
	// Add link: ListItem - ToolInfo
	infoFromItem.emplace(newItem, pInfo);
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
	fileName.clear(); // !!! allow open save dialog for new map
	return true;
}

QString MainForm::SaveMap()
{
	if (fileName.isEmpty())
	{
		QString fileNameHint = widget.mapArea->GetMapName();
		fileName = QFileDialog::getSaveFileName(this, "Save the map", fileNameHint, "Maps (*.map)");
		
		statusBar()->showMessage(fileName, 3000);
		
		// if user reconsider saving
		if (fileName.isEmpty())
			return fileName;
	}
	// Write file
	if (widget.mapArea->SaveToFile(fileName))
	{
		MapChanged(false);
	}
	else
	{
		fileName.clear();
		QMessageBox::critical(this, "Unable to save there!", "Try to save in other directory..");
	}
	return fileName;
}

void MainForm::MapChanged(bool yes)
{
	isMapSaved = !yes;
	widget.actionSave->setEnabled(yes);
	auto&& mapName = widget.mapArea->GetMapName();
	setWindowTitle(QString("%1 %2- %3")
			.arg(mapName)
			.arg(yes ? "(*) " : "")
			.arg(editorTitle));
}

}