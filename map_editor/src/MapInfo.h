#ifndef _MAPINFO_H
#define    _MAPINFO_H

#include <nya.hpp>

#include <QPixmap>
#include <QString>
#include <QPoint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>


//=========================================================================
struct ObjectInfo
{
	int id;
	QString name;
	QPixmap image;
	
	ObjectInfo(const int id, const QString name, const QPixmap image)
			: id(id), name(name), image(image) {}
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
	static std::map<int, s_p<ObjectInfo>> terrInfos;
	static std::map<int, s_p<ObjectInfo>> objInfos;
	
	std::string name;
	size_t width, height;
	std::vector<std::vector<Tile>> tiles;

public:
	MapInfo(const std::string& name, size_t width, size_t height);
	MapInfo(const QString& fileName);
	
	bool SaveToFile(QString fileName) const;
	bool LoadFromFile(QString fileName);
};

#endif    /* _MAPINFO_H */
