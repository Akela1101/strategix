/*
 * File:   StrategixLog.h
 * Author: Akela1101
 *
 * Created on 23 Апрель 2010 г., 23:25
 */

#ifndef _STRATEGIXLOG_H
#define    _STRATEGIXLOG_H

#include "StrategixSingleton.h"

#include <string>


#define STRATEGIX_DEBUG_LEVEL 2
#define STRATEGIX_DEBUG_SHOW // Show debug messages on screen
#define STRATEGIX_DEBUG_EXCEPTION // Show exception message in log


namespace Strategix
{
class Log : public StrategixSingleton<Log>
{
public:
	Log();
	void Write(const char* time, const char* level, const char* file, int line, std::string message, int tabs = 0);
};
}

#ifdef _DEBUG
#define STRATEGIX_LOG(message, level, tabs) Strategix::Log::GS().Write(__TIME__, level, __FILE__, __LINE__, message, tabs)

	#if STRATEGIX_DEBUG_LEVEL >= 2
		#define STRATEGIX_INFO(message) STRATEGIX_LOG(message, "info", 0)
	#else
		#define STRATEGIX_INFO(message)
	#endif

	#if STRATEGIX_DEBUG_LEVEL >= 1
		#define STRATEGIX_WARNING(message) STRATEGIX_LOG(message, "Warning", 1)
	#else
		#define STRATEGIX_WARNING(message)
	#endif

#define STRATEGIX_ERROR(message) STRATEGIX_LOG(message, "ERROR", 2)
#else
#define STRATEGIX_ERROR(message)
#endif

#endif    /* _STRATEGIXLOG_H */

