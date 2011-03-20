/* 
 * File:   LabelOObject.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 11:49
 */

#ifndef _LABELOOBJECT_H
#define	_LABELOOBJECT_H

#include "TitledOObject.h"
#include "CoordStructs.h"


namespace Sample1
{	
	class LabelOObject : public TitledOObject
	{
		Strategix::MapCoord mapCoord;

	public:
		LabelOObject(const std::string &meshName, const std::string &title, Strategix::MapCoord mapCoord);
		virtual ~LabelOObject();		
	};
}

#endif	/* _LABELOOBJECT_H */

