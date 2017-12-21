#pragma once

#include <Strategix_fwd.h>

namespace strx
{
using IdType = int;
using HpType = int;
using ResourceInfosType = vector<string>;
using TechTreesType = umap<string, u_p<TechTree>>;


static constexpr int maxMessageSize = 1e7; // about 10Mb


enum class PlayerType
{
	HUMAN,
	AI,
	NET
};

}
