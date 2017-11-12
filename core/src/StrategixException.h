#ifndef _STRATEGIXEXCEPTION_H
#define    _STRATEGIXEXCEPTION_H

#include "StrategixLog.h"

#include <exception>
#include <string>
#include <sstream>
#include <utility>


namespace Strategix
{
using namespace std;

class Exception : public std::exception
{
	const char* file;
	const int line;
	const string message;

public:
	Exception(const char* file, int line, string message)
			: file(file), line(line), message(std::move(message)) {}
	
	const char* what() const noexcept override
	{
		stringstream ss;
		ss << file << ":" << line << " >> " << message;
		return ss.str().c_str();
	}
};
}

#define STRATEGIX_THROW(message) throw Strategix::Exception(__FILE__, __LINE__, message)

#endif    /* _STRATEGIXEXCEPTION_H */

