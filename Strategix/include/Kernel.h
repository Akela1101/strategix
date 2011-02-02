/* 
 * File:   Kernel.h
 * Author: Akela1101
 *
 * Created on 13 Февраль 2010 г., 23:19
 */

#ifndef _KERNEL_H
#define	_KERNEL_H

#include "StrategixSingleton.h"
#include "TechTree.h"

#include "Game.h"
#include "GameStructs.h"

#include <string>
#include <vector>


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class Kernel : public StrategixSingleton<Kernel>
	{
	public:
		TechTreesType techTrees;

	public:
		Kernel();		
		virtual ~Kernel();

		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();
	};
}

#endif	/* _KERNEL_H */

