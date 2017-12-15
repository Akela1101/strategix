#ifndef _MapInfo_Forward_H
#define _MapInfo_Forward_H

#include <nya/enum.hpp>

namespace strx {}

namespace map_info
{
class MapInfo;
class MapWidget;
class ToolInfo;


#define ToolTypeDef(K, V)                      \
    K(TERRAIN)  /* terrain */                  \
    K(ENTITY)   /* player's entity */          \
    K(MINE)     /* resource mine */
nya_enum(ToolType, ToolTypeDef
)

using namespace strx;
}
#endif //_MapInfo_Forward_H
