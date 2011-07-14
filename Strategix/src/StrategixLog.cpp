/*
 * File:   StrategixLog.cpp
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 23:25
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "StrategixLog.h"


namespace Strategix
{
	using namespace std;

Log::Log()
{
	ofstream fout("Strategix.log", ios::trunc);
	fout.close();
}

void Log::Write(const char *time, const char *level, const char *file,
				const int line, const string message, const int tabs)
{
	stringstream ssLine; ssLine << line;
	ofstream fout("Strategix.log", ios::app);
	string sOut; sOut.reserve(200);
	for(int t = tabs; t; --t )
		sOut += "\t";
	sOut = string("[") + time + "] " + level + ": " + sOut + file	+ ":" + ssLine.str() + " >> " + message + "\n";
	fout << sOut;
	fout.close();
#ifdef STRATEGIX_DEBUG_SHOW
	cout << sOut;
#endif
}

}
