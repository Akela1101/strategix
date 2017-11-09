/* 
 * File:   StrategixException.h
 * Author: Akela1101
 *
 * Created on 14 Март 2010 г., 0:09
 */

#ifndef _STRATEGIXEXCEPTION_H
#define    _STRATEGIXEXCEPTION_H

#include "StrategixLog.h"

#include <exception>
#include <string>
#include <sstream>


namespace Strategix
{
using namespace std;

class Exception : public std::exception
{
	const char* file;
	const int line;
	const string message;

public:
	Exception(const char* file, const int line, const string message)
			: file(file), line(line), message(message) {}
	
	virtual ~Exception() throw() {}
	
	virtual const char* what() const throw()
	{
		stringstream ssLine;
		ssLine << line;
		string s = string("Exception in ") + file + ":" + ssLine.str() + " >> " + message;
		return s.c_str();
	}
};
}

#ifdef STRATEGIX_DEBUG_EXCEPTION
	#define STRATEGIX_EXCEPTION(message) { STRATEGIX_ERROR(message); throw Strategix::Exception(__FILE__, __LINE__, message); }
#else
	#define STRATEGIX_EXCEPTION(message) throw StrategixException(__FILE__, __LINE__, message)
#endif

#endif    /* _STRATEGIXEXCEPTION_H */

