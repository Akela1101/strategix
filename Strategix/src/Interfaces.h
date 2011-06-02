/* 
 * File:   Interfaces.h
 * Author: Akela1101
 *
 * Created on 18 Май 2011 г., 14:28
 */

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
		virtual void OnMove() {}
		virtual void OnMoveStop() {}
	};

	struct ICollect
	{
		virtual void OnCollectStart() {}
		virtual void OnCollect() {}
		virtual void OnCollectStop() {}
		virtual void OnBringStop() {}
	};
}

#endif	/* _INTERFACES_H */

