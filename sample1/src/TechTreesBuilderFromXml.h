#ifndef _TECHTREEBUILDERFROMXML_H
#define    _TECHTREEBUILDERFROMXML_H

#include <TechTreesBuilder.h>

#include <boost/property_tree/ptree.hpp>

#include <Strategix_Forward.h>


namespace Sample1
{
using namespace Strategix;
using namespace std;
namespace pt = boost::property_tree;

class EntiInfoMesh;

class TechTreesBuilderFromXml : public TechTreesBuilder
{
	TechTreesType* pTechTrees; // Link to building tree

public:
	void Build(TechTreesType* pTechTrees);

private:
	void BuildRace(const string& raceName, const pt::ptree& propTree);
	s_p<EntiInfoMesh> BuildEntity(const pt::ptree& entityPropTree);
	s_p<Resources> BuildResources(const pt::ptree& resourcesPropTree);
};
}

#endif    /* _TECHTREEBUILDERFROMXML_H */

