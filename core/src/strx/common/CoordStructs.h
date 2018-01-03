#pragma once

#include <ostream>
#include <boost/operators.hpp>

namespace strx
{
template<typename T, typename Y>
struct Coord
        : boost::totally_ordered<Coord<T, Y>
        , boost::additive<Coord<T, Y>
        , boost::multiplicative<Coord<T, Y>, float>>>
{
	T x, y;

	Coord() {}
	Coord(T x, T y) : x(x), y(y) {}
	Coord(const Coord& other) = default;
	Coord& operator =(const Coord& other) = default;

	operator Coord<Y, T>() const { return Coord<Y, T>(x, y); }

	bool operator ==(const Coord& other) const { return x == other.x && y == other.y; }
	bool operator <(const Coord& other) const { return x != other.x ? x < other.x : y < other.y; }
	Coord& operator +=(const Coord& other) { x += other.x, y += other.y; return *this; }
	Coord& operator -=(const Coord& other) { x -= other.x, y -= other.y; return *this; }
	Coord& operator *=(float value) { x *= value, y *= value; return *this; }

	float Len() const { return sqrtf(x * x + y * y); }
	Coord Norm() const { float invLen = 1.0 / Len(); return Coord(x * invLen, y * invLen); }
};

using MapCoord  = Coord<int, float>; // used in Maps
using RealCoord = Coord<float, int>; // used in Entity and everywhere

#ifdef MSCC
template<>
MapCoord::operator RealCoord() const
{
	return RealCoord(0.5 + x, 0.5 + y); // Center object in cell
}
#else // GCC
template<>
MapCoord::operator RealCoord() const;
#endif

template<typename T, typename Y>
std::ostream& operator <<(std::ostream& os, Coord<T, Y> coord)
{
	return os << "(" << coord.x << ", " << coord.y << ")";
}
}

namespace std
{
template<> struct hash<strx::MapCoord>
{
	static constexpr int shift = sizeof(size_t) * 8 / 2;

	size_t operator()(const strx::MapCoord& coord) const noexcept
	{
		return coord.x ^ ((size_t)coord.y << shift);
	}
};
}
