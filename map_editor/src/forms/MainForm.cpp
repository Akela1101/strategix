#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include "DialogNew.h"
#include "MainForm.h"


namespace map_editor
{
using namespace map_info;

static const char editorTitle[] = "Strategix Map Editor";

static const char* str(const QString& message) { return message.toUtf8().data(); }


MainForm::MainForm()
		: isMapOpened(false)
{
	widget.setupUi(this);
	
	setWindowTitle(editorTitle);
	widget.actionSave->setEnabled(false);
	
	MapInfo::LoadTerrainInfos();
	MapInfo::LoadObjectInfos();
	
	// terrains
	for (auto&& name_info : MapInfo::terrainInfos)
	{
		ListWidgetFill(ToolType::TERRAIN, name_info.first, widget.terrainListWidget);
	}
	
	// tools
	MapInfo::LoadMarkInfo("config/images/player_position.png");
	MapInfo::LoadMarkInfo("config/images/delete_object.png", ToolType::ERASE);
	ListWidgetFill(ToolType::MARK, "player_position", widget.toolsListWidget);
	ListWidgetFill(ToolType::ERASE, "delete_object", widget.toolsListWidget);
	
	// resources
	ListWidgetFill(ToolType::MINE, "gold", widget.resourceListWidget);
	ListWidgetFill(ToolType::MINE, "tree", widget.resourceListWidget);
	
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
		QString name = dialogNew.mapName;
		try
		{
			widget.mapArea->SetMap(name, dialogNew.mapWidth, dialogNew.mapHeight);
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
	if (!TrySaveMap()) return;
	
	QString loadedFileName = QFileDialog::getOpenFileName(this, "Load the map", "", "Maps (*.map)");
	if (loadedFileName.isEmpty()) return;
	
	fileName = loadedFileName;
	try
	{
		widget.mapArea->LoadFromFile(fileName);
	}
	catch (exception& e)
	{
		QMessageBox::critical(nullptr, QString("Error while reading the file: %1").arg(fileName), e.what());
		return;
	}
	isMapOpened = true;
	MapChanged(false);
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
void MainForm::ListWidgetFill(ToolType type, const std::string& name, QListWidget* listWidget)
{
	ToolInfo* info = nullptr;
	switch (type)
	{
		case ToolType::TERRAIN:
		{
			info = MapInfo::terrainInfos[name].get();
			break;
		}
		case ToolType::MARK:
		case ToolType::ERASE:
		{
			info = MapInfo::markInfos[name].get();
			break;
		}
		case ToolType::MINE:
		{
			info = MapInfo::objectInfos[name].get();
			break;
		}
	}
	// Add List entry
	QString title = QString(name.c_str()).replace('_', ' ');
	QListWidgetItem* newItem = new QListWidgetItem(QIcon(info->image), title);
	listWidget->addItem(newItem);
	
	// Add link: ListItem - ToolInfo
	infoFromItem.emplace(newItem, info);
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
	try
	{
		widget.mapArea->SaveToFile(fileName);
		MapChanged(false);
	}
	catch (exception& ex)
	{
		fileName.clear();
		QMessageBox::critical(this, "Unable to save map", ex.what());
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