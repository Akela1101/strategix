/* 
 * File:   OObjectTitled.h
 * Author: Akela1101
 *
 * Created on 18 Март 2011 г., 19:03
 */

#ifndef _OOBJECTTITLED_H
#define	_OOBJECTTITLED_H

#include "OObject.h"
#include "ObjectTitle.h"

#include "Sample1_Forward.h"


namespace Sample1
{
	using namespace std;

	class OObjectTitled : public OObject
	{
	protected:
		sh_p<ObjectTitle> objectTitle;

	public:
		OObjectTitled(const string &meshName, const string title = "")
			: OObject(meshName), objectTitle(new ObjectTitle(entity, title, "Calibri")) {}
		virtual ~OObjectTitled() {}
	};
}

#endif	/* _OOBJECTTITLED_H */

