/* 
 * File:   StraxLog.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 23:25
 */

#ifndef _STRAXLOG_H
#define	_STRAXLOG_H

#include "StraxSingleton.h"

namespace Strategix
{
	class StraxLog : public StraxSingleton<StraxLog>
	{
	public:
		StraxLog();
		void Log(const char *str);
	};
}

#endif	/* _STRAXLOG_H */

