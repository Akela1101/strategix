/* 
 * File:   Resources.cpp
 * Author: Akela1101
 * 
 * Created on 17 Май 2011 г., 10:52
 */

#include "KernelBase.h"

#include "Resources.h"


namespace Strategix
{

Resources::Resources()
	:
	resources(KernelBase::GS().GetResourceInfos().size(), 0)
{}

Resources::Resources(const int index, const ResType res)
	:
	resources(KernelBase::GS().GetResourceInfos().size(), 0)
{
	resources[index] = res;
}

Resources::Resources(const Resources &_c)
{
	init(_c);
}

Resources& Resources::operator =(const Resources &_c)
{
	if( this != &_c )
	{
		init(_c);
	}
	return *this;
}

void Resources::init(const Resources &_c)
{
	resources = _c.resources;
}

ResType& Resources::operator() (const string resourceName)
{
	return resources[KernelBase::GS().GetResourceInfo(resourceName).index];
}

const ResType& Resources::operator() (const string resourceName) const
{
	return resources[KernelBase::GS().GetResourceInfo(resourceName).index];
}

}
