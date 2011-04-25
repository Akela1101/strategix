/* 
 * File:   EntiInfoMesh.h
 * Author: Akela1101
 *
 * Created on 21 Апрель 2011 г., 15:01
 */

#ifndef _ENTIINFOMESH_H
#define	_ENTIINFOMESH_H

#include "EntiInfo.h"

#include <string>


namespace Sample1
{
	using namespace std;

	struct EntiInfoMesh : public Strategix::EntiInfo
	{
		string meshName;
		float meshScale;

		virtual EntiInfoMesh *copy() { return new EntiInfoMesh(*this); }
	};
}

#endif	/* _ENTIINFOMESH_H */

