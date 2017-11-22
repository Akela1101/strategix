#include <iomanip>
#include <fstream>
#include <QtGui>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QScrollBar>
#include <QWidget>
#include <Common.h>

#include <forms/MainForm.h>
#include "MapAreaWidget.h"

using namespace std;
using namespace common;


static constexpr int minZoom = 4;
static constexpr int maxZoom = 64;
static constexpr int tileLenBase = 64; // size of tile pixmap

struct MapInfo
{
	struct Tile
	{
		ToolInfo* terrain;
		ToolInfo* object; // can be null
	};
	
	QString name;
	int width, height;
	std::vector<std::vector<Tile>> tiles;
	
	MapInfo(const QString& name, int width, int height)
			: name(name), width(width), height(height)
	{
		try
		{
			CheckDimentions();
			
			tiles.reserve(height);
			for (int row = 0; row < height; ++row)
			{
				auto& t = tiles.emplace_back();
				t.reserve(width);
				for (int col = 0; col < width; ++col)
				{
					t.push_back({ terrainInfos["grass1"].get(), nullptr });
				}
			}
		}
		catch (exception& e)
		{
			QMessageBox::critical(nullptr, QString("Error creating map: %1").arg(name), e.what());
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

private:
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
		CheckDimentions();
		
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
				t.push_back({ GetTerrainById(id), nullptr });
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
	
	void CheckDimentions()
	{
		if (width < 10 || height < 10)
			throw_nya << "Minimum map dimensions (10x10) exceeded: %dx%d"s % width % height;
		if (width > 200 || height > 200)
			throw_nya << "Maximum map dimensions (200x200) exceeded: %dx%d"s % width % height;
	}
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MapAreaWidgetImpl : public QWidget
{
Q_OBJECT
	friend class MapAreaWidget;
	
	MainForm* mainForm;
	QScrollArea* scrollArea;
	umap<const QListWidgetItem*, ToolInfo*> infoFromItem;
	
	u_p<MapInfo> mapInfo;
	u_p<QPixmap> groundPixmap;
	u_p<QPixmap> frontPixmap;
	QRect rectBase;
	QRect rectScaled;
	QPoint lastPos;
	QPoint globalPos;
	QPoint lastGlobalPos;
	int tileLen;
	bool isHighlight;

public:
	MapAreaWidgetImpl(QScrollArea* parent)
			: QWidget(parent)
			, scrollArea(parent)
			, isHighlight(false)
	{
		setMouseTracking(true);
	}
	
	~MapAreaWidgetImpl() = default;


protected:
	void paintEvent(QPaintEvent*) override
	{
		if (!mapInfo) return;
		
		qreal scale = (qreal)tileLen / tileLenBase;
		
		QPainter painter(this);
		painter.scale(scale, scale);
		painter.drawPixmap(0, 0, *groundPixmap);
		painter.drawPixmap(0, 0, *frontPixmap);
		
		if (isHighlight)
		{
			painter.setBrush(QColor(250, 250, 100, 150));
			painter.setPen(Qt::NoPen);
			painter.drawRect(rectBase);
		}
	}
	
	void wheelEvent(QWheelEvent* event) override
	{
		if (!mapInfo) return;
		
		tileLen += copysign(4, event->delta());
		if (tileLen < minZoom) { tileLen = minZoom; return; }
		if (tileLen > maxZoom) { tileLen = maxZoom; return; }
		
		// Update view
		isHighlight = false;
		setFixedSize(groundPixmap->size() * tileLen / tileLenBase);
		update();
		
		// Move sliders to mouse center
		QScrollBar* hSB = scrollArea->horizontalScrollBar();
		int tilesNumberX = hSB->pageStep() / maxZoom;      // number of tiles on screen for max zoom
		int centralWidth = mapInfo->width - tilesNumberX;  // number of tiles in the center of screen
		int centralX = lastPos.x() - tilesNumberX / 2;     // position in central coordinates
		if (centralWidth < 1) centralWidth = 1;
		hSB->setSliderPosition(hSB->maximum() * centralX / centralWidth);
		
		QScrollBar* vSB = scrollArea->verticalScrollBar();
		int tilesNumberY = vSB->pageStep() / maxZoom;
		int centralHeight = mapInfo->height - tilesNumberY;
		int centralY = lastPos.y() - tilesNumberY / 2;
		if (centralHeight < 1) centralHeight = 1;
		vSB->setSliderPosition(vSB->maximum() * centralY / centralHeight);
	}
	
	void mouseMoveEvent(QMouseEvent* event) override
	{
		if (!mapInfo) return;
		
		const QPoint& point = event->pos();
		if (!this->rect().contains(point)) return;
			
		// Move sliders
		if (event->buttons() & Qt::RightButton)
		{
			globalPos = event->globalPos();
			
			QScrollBar* hSB = scrollArea->horizontalScrollBar();
			hSB->setSliderPosition(hSB->sliderPosition() - globalPos.x() + lastGlobalPos.x());
			QScrollBar* vSB = scrollArea->verticalScrollBar();
			vSB->setSliderPosition(vSB->sliderPosition() - globalPos.y() + lastGlobalPos.y());
			
			lastGlobalPos = globalPos;
		}
		
		QPoint pos(point.x() / tileLen, point.y() / tileLen);
		rectBase = QRect(pos.x() * tileLenBase, pos.y() * tileLenBase, tileLenBase, tileLenBase);
		
		// Draw objects, if LMB and current item is valid.
		if ((event->buttons() & Qt::LeftButton) && (mainForm->GetCurrentWidgetItem()))
		{
			isHighlight = false;
			
			auto& tile = mapInfo->tiles[pos.y()][pos.x()]; // On map
			ToolInfo* object = infoFromItem[mainForm->GetCurrentWidgetItem()]; // In mouse
			
			if (object && object->type == ToolType::TERRAIN)
			{
				ReplaceObject(*groundPixmap, rectBase, object, tile.terrain);
			}
			else
			{
				// delete, if object == null
				ReplaceObject(*frontPixmap, rectBase, object, tile.object);
			}
		}
		else // Highlight current rectangle
		{
			isHighlight = true;
		}
		
		// Update rects
		QRect newRectScaled = QRect(pos.x() * tileLen, pos.y() * tileLen, tileLen, tileLen);
		if (lastPos != pos)
		{
			update(rectScaled);
			update(newRectScaled);
			rectScaled = newRectScaled;
			lastPos = pos;
		}
	}
	
	void mousePressEvent(QMouseEvent* event) override
	{
		lastGlobalPos = event->globalPos();
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
	
	void mouseReleaseEvent(QMouseEvent* event) override
	{
		Q_UNUSED(event);
		
		releaseMouse();
	}

private:
	void ReplaceObject(QPixmap& pixmap, const QRect& rc, ToolInfo* object, ToolInfo*& currentObject)
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
	
	void SetMap(MapInfo* mapInfo)
	{
		this->mapInfo.reset(mapInfo);
		size_t width = mapInfo->width;
		size_t height = mapInfo->height;
		QSize groundSize((int) width * tileLenBase, (int) height * tileLenBase);
		
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
				const QRect& rc = QRect(col * tileLenBase, row * tileLenBase, tileLenBase, tileLenBase);
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
		
		tileLen = tileLenBase / 2;
		setFixedSize(groundSize * tileLen / tileLenBase);
		update();
	}
};
#include "MapAreaWidget.moc"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MapAreaWidget::MapAreaWidget(QWidget* parent)
		: QScrollArea(parent)
		, impl(new MapAreaWidgetImpl(this))
{
	setWidget(impl);
	setAlignment(Qt::AlignCenter);
}

MapAreaWidget::~MapAreaWidget() = default;

const QString& MapAreaWidget::GetMapName() const
{
	return impl->mapInfo->name;
}

void MapAreaWidget::SetInfoFromItem(const QListWidgetItem* item, ToolInfo* info)
{
	impl->infoFromItem.emplace(item, info);
}

void MapAreaWidget::AssignMainForm(MainForm* mainForm)
{
	impl->mainForm = mainForm;
}

void MapAreaWidget::SetMap(const QString& name, size_t width, size_t height)
{
	impl->SetMap(new MapInfo(name, width, height));
}

void MapAreaWidget::LoadFromFile(const QString& fileName)
{
	impl->SetMap(new MapInfo(fileName));
}

bool MapAreaWidget::SaveToFile(const QString& fileName) const
{
	impl->mapInfo->SaveToFile(fileName);
}

void MapAreaWidget::wheelEvent(QWheelEvent* event)
{
	event->ignore();
}
