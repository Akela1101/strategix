/* 
 * File:   Exception.h
 * Author: Akela1101
 *
 * Created on 14 Март 2010 г., 0:09
 */

#ifndef _STRATEGIXERROR_H
#define	_STRATEGIXERROR_H

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
		StrategixError(const char *file, int line, const char *message)
			:
			file(file),
			line(line),
			message(message)
		{}

		StrategixError(const char *file, int line, const string &message)
			:
			file(file),
			line(line),
			message(message.c_str())
		{}

		virtual ~StrategixError() throw() {}

		virtual const char* what() const throw()
		{
			stringstream ss;
			ss << "Error  on line " << line  << " in file: " << file << " >> " << message << endl;
			return ss.str().c_str();
		}
	};

	#define STRATEGIX_ERROR(message) throw StrategixError(__FILE__, __LINE__, message)
}

#endif	/* _STRATEGIXERROR_H */

