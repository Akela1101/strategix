/* 
 * File:   OObjectLabel.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 11:49
 */

#ifndef _OOBJECTLABEL_H
#define	_OOBJECTLABEL_H

#include "OObjectTitled.h"

#include <Strategix.h>


namespace Sample1
{
	using namespace Strategix;

	class OObjectLabel : public OObjectTitled
	{
		MapCoord mapCoord;

	public:
		OObjectLabel(const std::string &meshName, const std::string &title, MapCoord mapCoord);
		virtual ~OObjectLabel();		
	};
}

#endif	/* _OOBJECTLABEL_H */

