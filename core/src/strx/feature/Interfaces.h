#pragma once

#include <nya/signal.hpp>
#include <Strategix_fwd.h>

namespace strx
{
struct ICommand
{
	virtual void Completed(bool done) = 0;
};

struct IMove
{
	nya::sig<void(MapCoord coord)> DoMove;

	virtual void Moved(RealCoord coord) = 0;
	virtual void MapMoved(MapCoord from, MapCoord to) {}
};

struct ICollect
{
	nya::sig<void(MapCoord coord, const string& resourceName)> DoCollect;

	virtual void Collected() {}
};

struct IHealth
{
	virtual void HpChanged() {}
};

struct IAttack
{
	virtual void Attacked() {}
};
}
