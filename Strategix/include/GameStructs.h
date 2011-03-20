/* 
 * File:   GameStructs.h
 * Author: Akela1101
 *
 * Created on 12 Март 2010 г., 19:44
 */

#ifndef _GAMESTRUCTS_H
#define	_GAMESTRUCTS_H

#include <map>
#include <string>
#include <vector>

namespace Strategix
{
	using namespace std;

// EntiInfo
	typedef int HpType;
	typedef int ResType;
	typedef vector<string> Names;
	typedef float FeatureType;

	struct Params
	{		
		HpType hp;		
	};

	struct Action
	{
		string name;
		map<string, FeatureType> features;
	};

// PlayerType
	enum PlayerType
	{
		HUMAN,
		AI,
		NET
	};
}

#endif	/* _GAMESTRUCTS_H */

