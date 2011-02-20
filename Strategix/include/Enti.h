/* 
 * File:   Enti.h
 * Author: Akela1101
 *
 * Created on 4 Февраль 2011 г., 18:41
 */

#ifndef _ENTI_H
#define	_ENTI_H

#include <map>
#include <string>

#include "GameStructs.h"
#include "EntiInfo.h"


namespace Strategix
{
	using namespace std;

	class Enti
	{
	public:
		const EntiInfo *ei; // Link to tree
		Params params;
		map<string, Action> actions;
		MapCoord mapCoord;

	public:
		Enti(const EntiInfo *ei, const MapCoord &mapCoord);
		virtual ~Enti();

	private:
		Enti(const Enti &_c);
		Enti & operator =(const Enti &_c);
		inline void init(const Enti &_c);

	};
}
#endif	/* _ENTI_H */

