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
	class OObjectTitled : public OObject
	{
		sh_p<ObjectTitle> objectTitle;

	public:
		OObjectTitled(const std::string &meshName, const std::string &title)
			: OObject(meshName), objectTitle(new ObjectTitle(entity, title, "Calibri")) {}
		virtual ~OObjectTitled() {}

		void Update() { objectTitle->update(); }
		void Show(bool isShow) { objectTitle->show(isShow); }
	};
}

#endif	/* _OOBJECTTITLED_H */

