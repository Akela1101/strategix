/* 
 * File:   Enti.h
 * Author: Akela1101
 *
 * Created on 4 Февраль 2011 г., 18:41
 */

#ifndef _ENTI_H
#define	_ENTI_H

#include "GameStructs.h"
#include "CoordStructs.h"

#include <map>
#include <string>


namespace Strategix
{
	using namespace std;

	class Player;
	class EntiInfo;
	class Unit;

	class Enti
	{
	public:
		Player *player; // Link to owner
		const EntiInfo *ei; // Link to tree
		Params params;
		map<string, Action> actions;
		MapCoord mapCoord; // Change to realCoord!!!

		Unit *unit;

	public:
		Enti(const EntiInfo *ei, const MapCoord &mapCoord);
		virtual ~Enti();

	private:
		Enti(const Enti &_c);
		Enti & operator =(const Enti &_c);
	};
}
#endif	/* _ENTI_H */

