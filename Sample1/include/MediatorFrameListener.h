/* 
 * File:   MediatorFrameListener.h
 * Author: Akela1101
 *
 * Created on 13 Март 2011 г., 17:58
 */

#ifndef _MEDIATORFRAMELISTENER_H
#define	_MEDIATORFRAMELISTENER_H

#include "Ogre.h"

#include <vector>

#include "Nya.hpp"


namespace Sample1
{
	using namespace Ogre;

	class LabelUnit;

	class MediatorFrameListener : public FrameListener
	{
		typedef std::vector<sh_p<LabelUnit> > LabelVector;
		LabelVector labelVector;

	public:
		MediatorFrameListener();
		virtual ~MediatorFrameListener();

		void CreateLabels();
		void ShowLabels(bool isShow);

	private:
		MediatorFrameListener(const MediatorFrameListener &_c);
		MediatorFrameListener & operator =(const MediatorFrameListener &_c);

	};
}

#endif	/* _MEDIATORFRAMELISTENER_H */

