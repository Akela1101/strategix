#ifndef _MAPINFO_H
#define    _MAPINFO_H

#include <nya.hpp>
#include <memory>

#include <QHash>
#include <QList>
#include <QPixmap>
#include <QString>



//=========================================================================
struct ObjectInfo
{
	int id;
	QString name;
	QPixmap image;
	
	ObjectInfo(int id, const QString name, const QPixmap image)
			: id(id), name(name), image(image) {}
};

struct TerrainInfo
{
	QString name;
	float retard;
};

//=========================================================================
class MapInfo
{
public:
	struct Tile
	{
		s_p<ObjectInfo> terrain;
		s_p<ObjectInfo> object; // 0 - no objects
	};

public:
	// Infos maps, that are need for Load
	static QHash<int, s_p<ObjectInfo>> terrInfos;
	static QHash<int, s_p<ObjectInfo>> objInfos;
	
	QString name;
	size_t width, height;
	QList<QList<Tile>> tiles;

public:
	MapInfo(const QString& name, size_t width, size_t height);
	MapInfo(const QString& fileName);
	
	bool SaveToFile(const QString& fileName, const QList<TerrainInfo>& terrainInfos) const;
	bool LoadFromFile(const QString& fileName);
};

#endif    /* _MAPINFO_H */
