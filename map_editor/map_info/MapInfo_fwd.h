#pragma once

#include <nya/enum.hpp>

namespace strx {}

namespace map_info
{
struct MapInfo;
struct ToolInfo;

class MapWidget;


#define ToolTypeDef(K, V)                      \
	K(TERRAIN)  /* terrain */                  \
	K(ENTITY)   /* player's entity */          \
	K(MINE)     /* resource mine */
nya_enum(ToolType, ToolTypeDef
)

using namespace strx;
}
