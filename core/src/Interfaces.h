#ifndef _INTERFACES_H
#define	_INTERFACES_H

namespace Strategix
{
struct ICommand
{
	virtual void OnComplete(bool isComplete) = 0;
};

struct ITick
{
	virtual void OnTick(const float seconds) {}
};

struct IMove
{
	virtual void OnMoveStart() {}
	virtual void OnMove() = 0;
	virtual void OnMoveStop() {}
};

struct ICollect
{
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

#endif	/* _INTERFACES_H */

