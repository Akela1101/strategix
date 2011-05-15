/* 
 * File:   Log.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 23:25
 */

#ifndef _STRAXLOG_H
#define	_STRAXLOG_H

#include "StrategixSingleton.h"

namespace Strategix
{
	class Log : public StrategixSingleton<Log>
	{
	public:
		Log();
		void Write(const char *str);
	};
}

#endif	/* _STRAXLOG_H */

