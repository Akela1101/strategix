#include "../../strx/CoordStructs.hpp"


namespace strx
{
#ifndef _MSC_VER  // GCC

template<> MapCoord::operator RealCoord() const
{
	return RealCoord(0.5 + x, 0.5 + y);  // Center object in cell
}

#endif

}  // namespace strx
