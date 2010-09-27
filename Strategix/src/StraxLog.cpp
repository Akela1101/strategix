/* 
 * File:   StraxLog.cpp
 * Author: Akela1101
 * 
 * Created on 23 Апрель 2010 г., 23:25
 */

#include "StraxLog.h"
#include <fstream>

using namespace Strategix;
using namespace std;

StraxLog::StraxLog()
{
	ofstream fout("StraxLog.txt", ios::trunc);
	fout.close();
}

void StraxLog::Log(const char str[])
{
	ofstream fout("StraxLog.txt", ios::app);
	fout << str << endl;
	fout.close();
}

