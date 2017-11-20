#ifndef _STRATEGIXCOMMON_H
#define    _STRATEGIXCOMMON_H

#include <strx/common/Strategix_Forward.h>

namespace strx
{
using HpType = int;
using ResourceInfosType = vector<string>;
using TechTreesType = umap<string, u_p<TechTree>>;


enum class PlayerType
{
	HUMAN,
	AI,
	NET
};

/// Map cell
struct Cell
{
	int terrainType;
	float retard;
	Mine* mine;
};

}

#endif    /* _STRATEGIXCOMMON_H */

