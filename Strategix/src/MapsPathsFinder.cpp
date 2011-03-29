/* 
 * File:   MapsPathsFinder.cpp
 * Author: Akela1101
 * 
 * Created on 24 Март 2011 г., 17:14
 */

#include <list>

#include "MapsPathsFinder.h"
#include "MapsPath.h"


namespace Strategix
{

MapsPathsFinder::MapsPathsFinder()
{
}

MapsPathsFinder::~MapsPathsFinder()
{
}

//bool MapsPathsFinder::IsIn(const list<Cell*> &list, const Cell *cell) const
//{
//	return list.end() != find(list.begin(), list.end(), cell);
//}
//
//bool MapsPathsFinder::IsAccessible(const MapCoord &mc) const
//{
//	if( terrains[ cells[mc.y][mc.x].terrType ].retard <= 0 ) // water or mount
//		return false;
//	return true;
//}
//
//int MapsPathsFinder::Distance(const MapCoord &a, const MapCoord &b) const
//{
//	return (abs(a.x - b.x) + abs(a.y - b.y)) * 10;
//}

sh_p<MapsPath> MapsPathsFinder::FindPath(const MapCoord from, const MapCoord till)
{
//	list<CellPrice*> *p_closed = 0;
//	sh_p<MapsPath> way = FindPath_Debug(from, till, p_closed);
//	delete p_closed;

	sh_p<MapsPath> way;
	way->PutBack(till);
	return way;
}

//sh_p<MapsPath> MapsPathsFinder::FindPath_Debug(const MapCoord from, const MapCoord till, list<Cell*> *&p_closed)
//{
//	deque<MapCoord> *way = new deque<MapCoord>();
//
//	list<Cell*> opened;
//	delete p_closed; p_closed = new list<Cell*>();
//	list<Cell*> &closed = *p_closed;
//
//	Cell *current, *checking;
//
//	if( from.x == till.x && from.y == till.y )
//		return way;
//
//	static const MapCoord around[8] =
//	{
//		MapCoord(-1,  1), MapCoord( 0, 1), MapCoord( 1, 1),
//		MapCoord(-1,  0), MapCoord( 1,-1), MapCoord( 1, 0),
//		MapCoord(-1, -1), MapCoord( 0,-1) // <^ done for ability % 2
//	};
//
//	//
//	current = getCell(from);
//	current->parent = current;
//	current->G = current->H = current->F = 0;
//
//	opened.push_back(current);
//
//	bool is_found = false;
//	while( !opened.empty() )
//	{
//		list<Cell*>::iterator it_min, it = opened.begin();
//		it_min = it++;
//		Cell::Price F_min = (*it_min)->F;
//
//		for( ; it != opened.end(); ++it )
//		{
//			if( F_min > (*it)->F )
//			{
//				it_min = it;
//				F_min = (*it)->F;
//			}
//		}
//		opened.erase(it_min);
//		current = *it_min;
//		closed.push_front(current);
//
//		// Tsuite kita desu
//		if( current->mc == till )
//		{
//			is_found = true;
//			// Return list
//			Cell *from_cell = getCell(from);
//			for( ;current != from_cell; current = current->parent )
//			{
//				way->push_front(current->mc);
//			}
//			way->push_front(current->mc);
//
//			break;
//		}
//
//		for( int i = 0; i < 8; ++i )
//		{
//			MapCoord checking_mc = current->mc + around[i];
//
//			checking = getCell(checking_mc);
//			if( !checking || IsIn(closed, checking) || !IsAccessible(checking_mc) )
//				continue;
//
//			Cell::Price new_G = current->G + ((i % 2) ? 10 : 14) * current->retard; // sqrt(2)*10, 10
//
//			if( !IsIn(opened, checking) )
//			{
//				checking->parent = current;
//				checking->G = new_G;
//				checking->H = Distance(checking->mc, till);
//				checking->F = checking->G + checking->H;
//				opened.push_back(checking);
//			}
//			else
//			{
//				// in open list & mark < old mark
//				if( checking->G > new_G )
//				{
//					checking->parent = current;
//					checking->G = new_G;
//					checking->F = checking->G + checking->H;
//				}
//			}
//		}
//	}
//
//	return way;
//}

}
