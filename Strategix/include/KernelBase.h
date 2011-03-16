/* 
 * File:   KernelBase.h
 * Author: Akela1101
 *
 * Created on 13 Февраль 2010 г., 23:19
 */

#ifndef _KERNEL_H
#define	_KERNEL_H

#include "TechTree.h"
#include "StrategixSingleton.h"

#include <string>
#include <vector>


namespace Strategix
{
	using namespace std;
	using namespace boost;

	class KernelBase : public StrategixSingleton<KernelBase>
	{
	public:
		TechTreesType techTrees;

	public:
		KernelBase();
		virtual ~KernelBase();

		sh_p<vector<string> > GetMapNames();
		sh_p<vector<string> > GetRaceNames();
	};
}

#endif	/* _KERNEL_H */

