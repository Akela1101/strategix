#ifndef _RESOURCEINFOMESH_H
#define    _RESOURCEINFOMESH_H

#include <ResourceInfo.h>


namespace Sample1
{
using namespace std;

struct ResourceInfoMesh : Strategix::ResourceInfo
{
	const string meshName;
	
	ResourceInfoMesh(const string& name, const string& meshName)
			: ResourceInfo(name), meshName(meshName) {}
};
}

#endif    /* _RESOURCEINFOMESH_H */

