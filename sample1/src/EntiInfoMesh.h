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
	
	virtual EntiInfoMesh* copy() const
	{
		EntiInfoMesh* copy = new EntiInfoMesh();
		copy->init(*this);
		return copy;
	}

protected:
	void init(const EntiInfoMesh& _c)
	{
		EntiInfo::init(_c);
		meshName = _c.meshName;
		meshScale = _c.meshScale;
	}
};
}

#endif    /* _ENTIINFOMESH_H */

