#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using IdType = int;
using HpType = int;
using GameId = int;
using PlayerId = int;
using ResourceInfosType = s_p<vector<string>>;
using TechTreesType = umap<string, u_p<TechTree>>;


enum class PlayerType { HUMAN, AI };

}
