#include <forms/MainForm.h>
#include <Common.h>

#include <memory>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>
#include <QString>
#include <QScrollBar>
#include <nya.hpp>
#include <nya/exception.hpp>

#include "MapAreaWidget.h"

using namespace std;
using namespace common;


static QPoint globalPoint, lastGlobalPoint;

struct MapInfo
{
	struct Tile
	{
		ToolInfo* terrain;
		ToolInfo* object; // can be null
	};
	
	QString name;
	size_t width, height;
	std::vector<std::vector<Tile>> tiles;
	
	MapInfo(const QString& name, size_t width, size_t height)
			: name(name), width(width), height(height)
	{
		tiles.reserve(height);
		for (int row = 0; row < height; ++row)
		{
			auto& t = tiles.emplace_back();
			t.reserve(width);
			for (int col = 0; col < width; ++col)
			{
				t.push_back({terrainInfos["grass1"].get(), nullptr});
			}
		}
	}
	
	MapInfo(const QString& fileName)
	{
		try
		{
			LoadFromFile(fileName);
		}
		catch (exception& e)
		{
			QMessageBox::critical(nullptr, QString("Error while reading the file: %1").arg(fileName), e.what());
		}
	}
	
	bool SaveToFile(const QString& fileName) const
	{
		ofstream fout(fileName.toLocal8Bit());
		
		// Top string and version
		fout << mapFileTopString << "\n"
		     << editorVersion << "\n"
		     << "\n";
		
		// Dimensions
		fout << width << " " << height << "\n";
		
		vector<QPoint> playerPositions;
		vector<QPoint> objectPositions;
		
		// Terrain
		uset<TerrainInfo*> uniqueTerrains;
		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				auto& tile = tiles[row][col];
				auto terrain = (TerrainInfo*) tile.terrain;
				uniqueTerrains.insert(terrain);
				
				int id = terrain->id;
				fout << setw(2) << id << " ";
				
				if (tile.object)
				{
					if (tile.object->type == ToolType::PLAYER)
						playerPositions.emplace_back(col, row);
					else
						objectPositions.emplace_back(col, row);
				}
			}
			fout << "\n";
		}
		fout << "\n";
		
		// Terrain descriptions
		fout << uniqueTerrains.size() << "\n";
		for (TerrainInfo* terrain : uniqueTerrains)
		{
			int id = terrain->id;
			string name = terrain->name;
			float retard = terrain->retard;
			fout << id << " " << name << " " << retard << "\n";
		}
		fout << "\n";
		
		// Player initial positions
		fout << playerPositions.size() << "\n";
		for (auto&& pos : playerPositions)
		{
			fout << pos.x() << " " << pos.y() << "\n";
		}
		fout << "\n";
		
		// Mines
		fout << objectPositions.size() << "\n";
		for (auto&& pos : objectPositions)
		{
			fout << pos.x() << " " << pos.y() << " " << "gold" << " " << 100000 << "\n";
		}
		
		fout.close();
		return true;
	}
	
	void LoadFromFile(const QString& fileName)
	{
		name = QFileInfo(fileName).completeBaseName();
		
		ifstream fin(fileName.toLocal8Bit());
		string oneString;
		
		// Top string
		getline(fin, oneString);
		if (oneString != mapFileTopString)
			throw_nya << "%s is not a map file."s % fileName.toStdString();
		
		// Version
		getline(fin, oneString);
		if (oneString != editorVersion)
			throw_nya << "Version of map [%s] should be [%s]."s % oneString % editorVersion;
		
		// Dimensions
		fin >> width >> height;
		if (width > 200 || height > 200)
			throw_nya << "Maximum map dimensions (200x200) exceeded: %zux%zu"s % width % height;
		
		// Map content
		tiles.reserve(height);
		for (int row = 0; row < height; ++row)
		{
			auto& t = tiles.emplace_back();
			t.reserve(width);
			for (int col = 0; col < width; ++col)
			{
				int id;
				fin >> id;
				t.push_back({GetTerrainById(id), nullptr});
			}
		}
		
		// Terrain description
		int terrainsNumber;
		fin >> terrainsNumber;
		for (int i = 0; i < terrainsNumber; ++i)
		{
			int id;
			string terrainName;
			float retard;
			fin >> id >> terrainName >> retard;
		}
		
		// Player initial positions
		int n;
		fin >> n;
		for (int i = 0; i < n; ++i)
		{
			int row, col;
			fin >> col >> row;
			tiles[row][col].object = objectInfos[ToolType::PLAYER].get();
		}
		
		// Resources
		fin >> n;
		for (int i = 0; i < n; ++i)
		{
			int row, col, amount;
			string name;
			fin >> col >> row >> name >> amount;
			tiles[row][col].object = objectInfos[ToolType::MINE].get();
		}
		
		if (!fin.good())
			throw_nya << "Map content is corrupted!";
		fin.close();
	}
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MapAreaWidget::MapAreaWidget(QWidget* parent)
		: QWidget(parent)
		, tileSize(50)
		, isHighlight(false)
{
	setMouseTracking(true);
}

MapAreaWidget::~MapAreaWidget() = default;

const QString& MapAreaWidget::GetMapName() const
{
	return mapInfo->name;
}

void MapAreaWidget::AssignMainForm(MainForm* mainForm, QScrollArea* scrollArea)
{
	this->mainForm = mainForm;
	this->scrollArea = scrollArea;
}

void MapAreaWidget::SetMap(const QString& name, size_t width, size_t height)
{
	SetMap(new MapInfo(name, width, height));
}

void MapAreaWidget::LoadFromFile(const QString& fileName)
{
	SetMap(new MapInfo(fileName));
}

bool MapAreaWidget::SaveToFile(const QString& fileName) const
{
	mapInfo->SaveToFile(fileName);
}

void MapAreaWidget::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	
	if (!mapInfo)
		return;
	
	QPainter painter(this);
	painter.drawPixmap(0, 0, *groundPixmap);
	painter.drawPixmap(0, 0, *frontPixmap);
	
	if (isHighlight)
	{
		painter.setBrush(QColor(250, 250, 100, 150));
		painter.setPen(Qt::NoPen);
		painter.drawRect(lastRc);
	}
}

void MapAreaWidget::mouseMoveEvent(QMouseEvent* event)
{
	const QPoint& point = event->pos();
	
	if (!mapInfo || !this->rect().contains(point))
		return;
	
	// Move sliders
	if (event->buttons() & Qt::RightButton)
	{
		globalPoint = event->globalPos();
		
		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		hSB->setSliderPosition(hSB->sliderPosition() - globalPoint.x() + lastGlobalPoint.x());
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		vSB->setSliderPosition(vSB->sliderPosition() - globalPoint.y() + lastGlobalPoint.y());
		
		lastGlobalPoint = globalPoint;
	}
	
	int tileX = point.x() / tileSize;
	int tileY = point.y() / tileSize;
	const QRect& rc = QRect(tileX * tileSize, tileY * tileSize, tileSize, tileSize);
	
	// Draw objects, if LMB and current item is valid.
	if ((event->buttons() & Qt::LeftButton) && (mainForm->GetCurrentWidgetItem()))
	{
		isHighlight = false;
		
		auto& tile = mapInfo->tiles[tileY][tileX]; // On map
		ToolInfo* object = infoFromItem[mainForm->GetCurrentWidgetItem()]; // In mouse
		
		if (object && object->type == ToolType::TERRAIN)
		{
			ReplaceObject(*groundPixmap, rc, object, tile.terrain);
		}
		else
		{
			// delete, if object == null
			ReplaceObject(*frontPixmap, rc, object, tile.object);
		}
	}
	else // Highlight current rectangle
	{
		isHighlight = true;
	}
	
	// Update rects
	if (lastRc.topLeft() != rc.topLeft())
	{
		update(lastRc);
		lastRc = rc;
		update(lastRc);
	}
}

void MapAreaWidget::mousePressEvent(QMouseEvent* event)
{
	lastGlobalPoint = event->globalPos();
	if (event->buttons() & Qt::RightButton)
	{
		grabMouse(QCursor(Qt::ClosedHandCursor));
	}
	else
	{
		grabMouse();
	}
	
	mouseMoveEvent(event); // for single mouse click processing
}

void MapAreaWidget::mouseReleaseEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	
	releaseMouse();
}

void MapAreaWidget::ReplaceObject(QPixmap& pixmap, const QRect& rc, ToolInfo* object, ToolInfo*& currentObject)
{
	if (currentObject == object) return;
	
	currentObject = object;
	{
		QPainter painter(&pixmap);
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		if (object)
			painter.drawPixmap(rc, object->image);
		else
			painter.fillRect(rc, QColor(0, 0, 0, 0));
	}
	update(rc);
	
	mainForm->MapChanged();
}

void MapAreaWidget::SetMap(MapInfo* mapInfo)
{
	this->mapInfo.reset(mapInfo);
	size_t width = mapInfo->width;
	size_t height = mapInfo->height;
	auto groundSize = QSize((int) width * tileSize, (int) height * tileSize);
	
	groundPixmap.reset(new QPixmap(groundSize));
	frontPixmap.reset(new QPixmap(groundSize));
	frontPixmap->fill(QColor(0, 0, 0, 0)); // Necessary clear!
	
	// Draw ground and objects
	QPainter groundPainter, frontPainter;
	groundPainter.begin(groundPixmap.get());
	frontPainter.begin(frontPixmap.get());
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width; ++col)
		{
			const QRect& rc = QRect(col * tileSize, row * tileSize, tileSize, tileSize);
			auto&& tile = mapInfo->tiles[row][col];
			groundPainter.drawPixmap(rc, tile.terrain->image);
			if (tile.object)
			{
				frontPainter.drawPixmap(rc, tile.object->image);
			}
		}
	}
	groundPainter.end();
	frontPainter.end();
	
	setFixedSize(groundSize);
	update();
}