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


namespace Strategix
{
	using namespace std;
	
	class StraxError : public std::exception
	{
		const char *file;
		int line;
		const char *message;

	public:
		StraxError(const char *_file, int _line, const char *_message) throw()
		{
			file = _file;
			line = _line;
			message = _message;
		}

		virtual ~StraxError() throw() {}

		virtual const char* what() const throw()
		{
			stringstream ss;
			ss << "Error in " << file << " on line = " << line << endl
				<< message << endl;
			return ss.str().c_str();
		}
	};

	#define STRAX_ERROR(message) StraxError(__FILE__, __LINE__, message)
}

#endif	/* _EXCEPTION_H */

