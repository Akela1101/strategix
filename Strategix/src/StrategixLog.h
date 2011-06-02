/* 
 * File:   StrategixLog.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 23:25
 */

#ifndef _STRATEGIXLOG_H
#define	_STRATEGIXLOG_H

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

#endif	/* _STRATEGIXLOG_H */

