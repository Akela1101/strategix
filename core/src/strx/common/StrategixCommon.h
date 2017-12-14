#ifndef _STRATEGIXCOMMON_H
#define    _STRATEGIXCOMMON_H

#include <Strategix_Forward.h>

namespace strx
{
using IdType = int;
using HpType = int;
using ResourceInfosType = vector<string>;
using TechTreesType = umap<string, u_p<TechTree>>;


enum class PlayerType
{
	HUMAN,
	AI,
	NET
};

}

#endif    /* _STRATEGIXCOMMON_H */

