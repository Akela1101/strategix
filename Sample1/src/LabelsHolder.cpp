/* 
 * File:   LabelsHolder.cpp
 * Author: Akela1101
 * 
 * Created on 13 Март 2011 г., 17:58
 */

#include "LabelOObject.h"
#include "MyAppCommon.h"

#include "Map.h"
#include "Kernel.h"

#include <Ogre.h>

#include "LabelsHolder.h"


namespace Sample1
{
	static char labelsPointMeshName[] = "LabelsPointMesh";

LabelsHolder::LabelsHolder()
{
	// Creating point mesh for all labels to cling to
	static bool isNoMesh = true;
	if( isNoMesh )
	{
		ManualObject mo("TilePoint");
		mo.begin("BaseWhiteNoLighting", RenderOperation::OT_POINT_LIST);
		mo.position(0, 0, 0);
		mo.end();
		mo.convertToMesh(labelsPointMeshName);

		isNoMesh = false;
	}
}

LabelsHolder::~LabelsHolder()
{
}

// Labels on every cell of Map, showing retard of terrain.
void LabelsHolder::CreateLabels()
{
//	const Strategix::Map &map = Strategix::kernel->GetMap();
//	const int width = map.GetWidth();
//	const int length = map.GetLength();
//
//	labelVector.reserve(width * length);
//
//	for( int x = 0; x < width; ++x )
//	{
//		for( int z = 0; z < length; ++z )
//		{
//			std::stringstream title;
//			title << "   " << map(x, z).retard;
//			sh_p<LabelOObject> labelUnit(new LabelOObject(
//				labelsPointMeshName, title.str().c_str(), Strategix::MapCoord(x, z)));
//
//			labelUnit->SetColor(ColourValue(1.0, 0.4, 0.4, 1.0));
//
//			labelVector.push_back(labelUnit);
//		}
//	}
}

void LabelsHolder::ShowLabels(bool isShow)
{
	for( LabelVector::iterator it = labelVector.begin(); it != labelVector.end(); ++it )
	{
		(*it)->objectTitle->show(isShow);
	}
}

}