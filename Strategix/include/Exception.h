/* 
 * File:   Exception.h
 * Author: Akela1101
 *
 * Created on 14 Март 2010 г., 0:09
 */

#ifndef _EXCEPTION_H
#define	_EXCEPTION_H

#include <exception>
#include <sstream>
#include <string>


namespace Strategix
{
	using namespace std;
	
	class StrategixError : public std::exception
	{
		const char *file;
		int line;
		const char *message;

	public:
		StrategixError(const char *_file, int _line, const char *_message) throw()
		{
			file = _file;
			line = _line;
			message = _message;
		}

		StrategixError(const char *_file, int _line, const string &_message) throw()
		{
			file = _file;
			line = _line;
			message = _message.c_str();
		}

		virtual ~StrategixError() throw() {}

		virtual const char* what() const throw()
		{
			stringstream ss;
			ss << "Error  on line " << line  << " in file: " << file << " >> " << message << endl;
			return ss.str().c_str();
		}
	};

	#define STRATEGIX_ERROR(message) StrategixError(__FILE__, __LINE__, message)
}

#endif	/* _EXCEPTION_H */

