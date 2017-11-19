#ifndef _STRATEGIXCOMMON_H
#define    _STRATEGIXCOMMON_H

#include <common/Strategix_Forward.h>

namespace strategix
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

