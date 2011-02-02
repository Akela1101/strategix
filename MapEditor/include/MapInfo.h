/* 
 * File:   MapInfo.h
 * Author: Akela1101
 *
 * Created on 8 Сентябрь 2010 г., 23:19
 */

#ifndef _MAPINFO_H
#define	_MAPINFO_H

#include "Nya.hpp"

#include <QPixmap>
#include <QString>
#include <QPoint>
#include <set>
#include <map>
#include <string>


//=========================================================================
struct ObjectInfo
{
	int id;
	QString name;
	QPixmap image;

	ObjectInfo(const int id, const QString name, const QPixmap image)
		: id(id), name(name), image(image)
	{}
};

//=========================================================================
class MapInfo
{
public:
	struct Tile
	{
		sh_p<ObjectInfo> terrain;
		sh_p<ObjectInfo> object; // 0 - no objects
	};

public:
	// Infos maps, that are need for Load
	static std::map<int, sh_p<ObjectInfo> > terrInfos;
	static std::map<int, sh_p<ObjectInfo> > objInfos;

	std::string name;
	int width, height;
	sh_a<sh_a<Tile> > tiles;	

public:
	MapInfo(const std::string &name, const int width, const int height);
	MapInfo(const QString &fileName);
	virtual ~MapInfo();
		
	bool SaveToFile(QString fileName) const;
	bool LoadFromFile(QString fileName);
};

#endif	/* _MAPINFO_H */
