#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

#include "Common.h"


namespace common
{
const char editorTitle[] = "Strategix Map Editor";
const char editorVersion[] = "0.0.1";
const char mapFileTopString[] = "Strategix Map";
const char terrainsDefinitionFileName[] = "terrains.def";
const char configDir[] = "config/";
const char imagesPath[] = "config/images/";

umap<std::string, u_p<TerrainInfo>> terrainInfos;
umap<ToolType, u_p<ToolInfo>> objectInfos;

const char* str(const QString& message) { return message.toUtf8().data(); }

TerrainInfo* GetTerrainById(int id)
{
	using namespace boost;
	using namespace boost::adaptors;
	return find_if(terrainInfos | map_values, [id](auto&& info) { return info->id == id; })->get();
}

}