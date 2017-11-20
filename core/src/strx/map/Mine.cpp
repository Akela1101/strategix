#include "Mine.h"


namespace strx
{
ResourceUnit Mine::PickResource(ResourceUnit amount)
{
	if (*resource > amount)
	{
		*resource -= amount;
		return amount;
	}
	
	// remove if nothing left
	ResourceUnit remain = *resource;
	*resource -= remain;
	return remain;
}
}