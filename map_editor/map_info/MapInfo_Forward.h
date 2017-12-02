#ifndef _MapInfo_Forward_H
#define _MapInfo_Forward_H

#include <nya/enum.hpp>


namespace map_info
{
class MapInfo;
class ToolInfo;


#define ToolTypeDef(K, V)                      \
    K(TERRAIN)  /* terrain */                  \
    K(OBJECT)   /* map objects */              \
    K(MINE)     /* resource mine */
nya_enum(ToolType, ToolTypeDef
)

}
#endif //_MapInfo_Forward_H
