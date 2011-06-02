/* 
 * File:   LabelsHolder.h
 * Author: Akela1101
 *
 * Created on 13 Март 2011 г., 17:58
 */

#ifndef _LABELSHOLDER_H
#define	_LABELSHOLDER_H

#include <Ogre.h>
#include <vector>

#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace Ogre;

	class LabelsHolder
	{
		typedef std::vector<sh_p<OObjectLabel> > LabelVector;
		LabelVector labelVector;

	public:
		LabelsHolder();
		virtual ~LabelsHolder() {}

		void CreateLabels();
		void ShowLabels(bool isShow);

	private:
		LabelsHolder(const LabelsHolder &_c);
		LabelsHolder & operator =(const LabelsHolder &_c);

	};
}

#endif	/* _LABELSHOLDER_H */

