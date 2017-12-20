#pragma once

#include <nya/signal.hpp>
#include <Strategix_Forward.h>

namespace strx
{
struct ICommand
{
	virtual void OnComplete(bool isComplete) = 0;
};

struct ITick
{
	virtual void OnTick(float seconds) {}
};

struct IMove
{
	nya::sig<void(MapCoord coord)> DoMove;
	
	virtual void OnMoveStart() {}
	virtual void OnMove(RealCoord coord) = 0;
	virtual void OnMapMove(MapCoord from, MapCoord to) {}
	virtual void OnMoveStop() {}
};

struct ICollect
{
	nya::sig<void(MapCoord coord, const string& resourceName)> DoCollect;
	
	virtual void OnCollectStart() {}
	virtual void OnCollect() {}
	virtual void OnCollectStop() {}
	virtual void OnBringStop() {}
};

struct IHealth
{
	virtual void OnHpChange() {}
};

struct IAttack
{
	virtual void OnAttackStart() {}
	virtual void OnAttack() {}
	virtual void OnAttackStop() {}
};
}
