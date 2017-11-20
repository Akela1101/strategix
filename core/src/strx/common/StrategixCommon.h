#ifndef _STRATEGIXCOMMON_H
#define    _STRATEGIXCOMMON_H

#include <strx/common/Strategix_Forward.h>

namespace strx
{
enum PlayerType
{
	HUMAN,
	AI,
	NET
};

typedef float HpType;

/// Map cell
struct Cell
{
	int terrainType;
	float retard;
	Mine* mine;
};

}

#endif    /* _STRATEGIXCOMMON_H */

