/* 
 * File:   EntiInfo.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 18:34
 */

#ifndef _ENTIINFO_H
#define    _ENTIINFO_H

#include "KernelBase.h"
#include "FeatureInfo.h"
#include "Resources.h"

#include <map>
#include <string>
#include <vector>

#include "Strategix_Forward.h"


namespace Strategix
{
using namespace std;

struct EntiInfo
{
	string name;
	string kind; // building or entiSlot
	s_p<Resources> resources;
	vector<string> depends;
	vector<string> provides;
	
	typedef map<string, s_p<FeatureInfo>> FeatureInfosType;
	FeatureInfosType featureInfos;
	
	EntiInfo() : resources(KernelBase::GS().MakeResources()) {}
	
	virtual ~EntiInfo() = default;
	
	// virtual copy constructor
	virtual EntiInfo* copy() const
	{
		auto* copy = new EntiInfo();
		copy->init(*this);
		return copy;
	}

protected:
	void init(const EntiInfo& _c)
	{
		name = _c.name;
		kind = _c.kind;
		*resources = *_c.resources;
		depends = _c.depends;
		provides = _c.provides;
		
		for (const auto& pa : _c.featureInfos)
		{
			featureInfos[pa.first].reset(pa.second->copy());
		}
	}

	EntiInfo(const EntiInfo& _c) = delete;
	EntiInfo& operator=(const EntiInfo& _c) = delete;
};
}

#endif    /* _ENTIINFO_H */

