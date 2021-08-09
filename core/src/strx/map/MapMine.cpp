#include "MapMine.h"


namespace strx
{
ResourceUnit MapMine::PickResource(ResourceUnit amountChange)
{
	if (amount > amountChange)
	{
		amount -= amountChange;
		return amountChange;
	}

	ResourceUnit remain = amount;
	amount = 0;
	return remain;
}
}  // namespace strx