#pragma once

#include <nya.hpp>

namespace strx
{
using namespace std;

using IdType = int;
using HpType = int;
using GameId = int;
using PlayerId = int;
using ResourceInfosType = s_p<vector<string>>;
using TechTreesType = umap<string, u_p<TechTree>>;

enum class PlayerType
{
	HUMAN,
	AI
};
}  // namespace strx
