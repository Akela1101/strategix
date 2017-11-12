#include "MainForm.h"
#include "DialogNew.h"

#include <QMessageBox>
#include <QFileDialog>
#include <fstream>


const char mapFileTopString[] = "Strategix Map v.0.1";
const char terrainsDefinitionFileName[] = "terrains.def";
static const char sTitle[] = "Map Editor";

QString MainForm::GetMapsPath() const
{
	return QDir::currentPath() + "/maps/";
}

//===========================================================================

MainForm::MainForm()
{
	static const QString configPath = "config/";
	static const QString imagesPath = configPath + "images/";
	
	widget.setupUi(this);
	
	this->setWindowTitle(sTitle);
	
	isMapOpened = false;
	widget.actionSave->setEnabled(false);
	currentItem = nullptr;
	
	char terrainsImageFileName[100];
	int divs;
	std::vector<std::string> terrainNames;
	
	// Load description
	{
		using namespace std;
		
		ifstream fin((configPath + terrainsDefinitionFileName).toStdString().c_str());
		fin.getline(terrainsImageFileName, 100);
		fin >> divs;
		
		float retard; // No need here
		string terrName;
		for (;;)
		{
			fin >> retard >> terrName;
			if (!fin.good())
				break;
			
			terrainNames.push_back(terrName);
		}
		fin.close();
	}
	
	// 1. Load terrain images and add them as icons to List.
	QPixmap pixmap;
	if (!pixmap.load(configPath + terrainsImageFileName))
	{
		QMessageBox::warning(this, tr("Open Image"), tr("The image files could not be loaded."), QMessageBox::Cancel);
		return;
	}
	int tileSize = pixmap.width() / divs;
	
	for (int row = 0; row < divs; ++row)
	{
		for (int col = 0; col < divs; ++col)
		{
			int terrId = divs * row + col; // Index of picture will become terrain type!!!
			const QString& terrName = QString(terrainNames[terrId].c_str());
			if (terrName == "none") // none name are skipped !!!
				break;
			const QPixmap& terrPixmap = pixmap.copy(col * tileSize, row * tileSize, tileSize, tileSize);
			
			AddToListWidget(terrId, terrName, terrPixmap, &MapInfo::terrInfos, widget.terrainListWidget);
		}
	}
	
	// 2. Resources
	pixmap.load(imagesPath + "gold.png");
	AddToListWidget(1, "Gold", pixmap, &MapInfo::objInfos, widget.resourceListWidget);
	
	
	// 0. Tools
	// Player's initial positions
	pixmap.load(imagesPath + "player_position.png");
	AddToListWidget(0, "Set Player Position", pixmap, &MapInfo::objInfos, widget.toolsListWidget);
	
	// Delete object button
	pixmap.load(imagesPath + "delete_button.png");
	AddToListWidget(-1, "Delete object", pixmap, nullptr, widget.toolsListWidget);
	
	
	// Set Current
	currentToolboxIndex = widget.toolBox->currentIndex();
	
	//
	widget.mapArea->SetPs(this, widget.scrollArea);
}

void MainForm::FileNew()
{
	if (!TrySaveMap())
		return;
	
	DialogNew dialogNew;
	if (dialogNew.exec() == QDialog::Accepted)
	{
		const std::string& mapName = dialogNew.mapName.toStdString();
		const size_t& mapWidth = dialogNew.mapWidth;
		const size_t& mapHeight = dialogNew.mapHeight;
		s_p<MapInfo> mapInfo(new MapInfo(mapName, mapWidth, mapHeight));
		widget.mapArea->SetMap(mapInfo);
		
		isMapOpened = true;
		widget.actionSave->setEnabled(true);
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
	
	QString loadFileName = QFileDialog::getOpenFileName(this, "Load the map", GetMapsPath(), "Maps (*.map)");
	
	if (!loadFileName.isEmpty())
	{
		fileName = loadFileName;
		s_p<MapInfo> mapInfo(new MapInfo(fileName));
		widget.mapArea->SetMap(mapInfo);
		
		isMapOpened = true;
		widget.actionSave->setEnabled(false);
	}
}

void MainForm::FileExit()
{
	// Setted to close() by Designer
	// Change it. And ask for save, if not saved
}

void MainForm::HelpAbout()
{
	QMessageBox::about(this, "Map Editor For Sample1", "Map Editor v.0.1 \n (C) 2010-2017 Akela1101");
}

void MainForm::CurrentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
	Q_UNUSED(previous);
	
	currentItem = current;
	if (currentItem)
		this->statusBar()->showMessage(currentItem->text());
	else
		this->statusBar()->showMessage("***");
}

void MainForm::CurrentToolboxItemChanged(int index)
{
	currentToolboxIndex = index;
	
	const QListWidget* listWidget = dynamic_cast<QListWidget*>(widget.toolBox->widget(index)->children().last());
	// ^ Why last - i don't know ^_^
	
	CurrentItemChanged(listWidget->currentItem(), nullptr);
}

//------------------------------------------------------------------------------
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
		fileName = QFileDialog::getSaveFileName(this, "Save the map", GetMapsPath(), "Maps (*.map)");
		
		this->statusBar()->showMessage(fileName, 3000);
		
		// if user reconsider saving
		if (fileName.isEmpty())
			return fileName;
	}
	// Write file
	if (widget.mapArea->GetMapInfo()->SaveToFile(fileName))
	{
		isMapSaved = true;
		widget.actionSave->setEnabled(false);
		QString pathlessName(widget.mapArea->GetMapInfo()->name.c_str());
		this->setWindowTitle(pathlessName.section('/', -1) + " - " + sTitle);
	}
	else
	{
		fileName.clear();
		QMessageBox::critical(this, "Unable to save there!", "Try to save in other directory..");
	}
	return fileName;
}

void MainForm::MapChanged()
{
	// Able to write file ^
	isMapSaved = false;
	widget.actionSave->setEnabled(true);
	QString pathlessName(widget.mapArea->GetMapInfo()->name.c_str());
	this->setWindowTitle(pathlessName.section('/', -1) + " (*) - " + sTitle);
}

void MainForm::AddToListWidget(int objId, QString name, QPixmap pixmap
		, std::map<int, s_p<ObjectInfo>>* pInfos, QListWidget* listWidget)
{
	s_p<ObjectInfo> info;
	if (objId != -1)
	{
		info.reset(new ObjectInfo(objId, name, pixmap));
		pInfos->insert(std::pair<int, s_p<ObjectInfo>>(objId, info));
	}
	
	// Add List entry
	QListWidgetItem* newItem = new QListWidgetItem(QIcon(pixmap), name);
	listWidget->addItem(newItem);
	
	// Add link: ListItem - ObjectInfo
	widget.mapArea->objectFromItem[newItem] = info;
}