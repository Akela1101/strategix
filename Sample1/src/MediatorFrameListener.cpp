/* 
 * File:   MediatorFrameListener.cpp
 * Author: Akela1101
 * 
 * Created on 13 Март 2011 г., 17:58
 */

#include "LabelUnit.h"
#include "MyAppCommon.h"

#include "Map.h"
#include "Kernel.h"

#include "MediatorFrameListener.h"


namespace Sample1
{

MediatorFrameListener::MediatorFrameListener()
{
}

MediatorFrameListener::~MediatorFrameListener()
{
}

// Labels on every cell of Map, showing retard of terrain.
void MediatorFrameListener::CreateLabels()
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
//			sh_p<LabelUnit> labelUnit(new LabelUnit(Strategix::MapCoord(x, z), title.str().c_str()));
//
//			labelUnit->SetColor(ColourValue(1.0, 0.4, 0.4, 1.0));
//
//			labelVector.push_back(labelUnit);
//		}
//	}
}

void MediatorFrameListener::ShowLabels(bool isShow)
{
	for( LabelVector::iterator it = labelVector.begin(); it != labelVector.end(); ++it )
	{
		(*it)->Show(isShow);
	}
}

}