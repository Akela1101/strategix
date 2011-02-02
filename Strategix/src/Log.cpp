/* 
 * File:   Log.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 23:25
 */

#include "Log.h"
#include <fstream>

using namespace Strategix;
using namespace std;

Log::Log()
{
	ofstream fout("Log.txt", ios::trunc);
	fout.close();
}

void Log::Write(const char str[])
{
	ofstream fout("Log.txt", ios::app);
	fout << str << endl;
	fout.close();
}

