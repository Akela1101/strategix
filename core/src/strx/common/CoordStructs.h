#ifndef _COORDSTRUCTS_H
#define    _COORDSTRUCTS_H


namespace strx
{
template<typename T, typename Y>
struct Coord
{
	T x, y;
	
	Coord() {}
	Coord(const Coord& other) : x(other.x), y(other.y) {}
	Coord(T x, T y) : x(x), y(y) {}
	
	operator Coord<Y, T>() const
	{
		return Coord<Y, T>(x, y);
	}
	
	bool operator ==(const Coord& other) const
	{
		return x == other.x && y == other.y;
	}
	
	bool operator !=(const Coord& other) const
	{
		return x != other.x || y != other.y;
	}
	
	Coord operator +(const Coord& other) const
	{
		return Coord(x + other.x, y + other.y);
	}
	
	Coord operator -(const Coord& other) const
	{
		return Coord(x - other.x, y - other.y);
	}
	
	Coord& operator +=(const Coord& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	
	Coord& operator -=(const Coord& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	
	Coord operator *(float value)
	{
		return Coord(value * x, value * y);
	}
	
	bool operator <(const Coord& other)
	{
		return x != other.x ? x < other.x : y < other.y;
	}
	
	T Len() const
	{
		return x * x + y * y;
	}
	
	Coord Norm() const
	{
		float invLen = 1.0 / Len();
		return Coord(x * invLen, y * invLen);
	}
};

using MapCoord  = Coord<int, float>; // used in Maps
using RealCoord = Coord<float, int>; // used in Enti and everywhere

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

#endif    /* _COORDSTRUCTS_H */

