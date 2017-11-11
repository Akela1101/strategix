#ifndef _ENTIINFOMESH_H
#define    _ENTIINFOMESH_H

#include <EntiInfo.h>

#include <string>


namespace Sample1
{
using namespace std;
using namespace Strategix;

struct EntiInfoMesh : public Strategix::EntiInfo
{
	string meshName;
	float meshScale;
	
	EntiInfoMesh() : EntiInfo() {}
	
	EntiInfoMesh(const EntiInfoMesh& _c)
		: EntiInfo(_c)
	{
		meshName = _c.meshName;
		meshScale = _c.meshScale;
	}
	
	EntiInfoMesh* clone() const override { return new EntiInfoMesh(*this); }
};
}

#endif    /* _ENTIINFOMESH_H */

