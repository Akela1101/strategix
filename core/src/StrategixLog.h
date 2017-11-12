#ifndef _STRATEGIXLOG_H
#define    _STRATEGIXLOG_H

#include "StrategixSingleton.h"

#include <string>


#define STRATEGIX_DEBUG_LEVEL 2
#define STRATEGIX_DEBUG_SHOW // Show debug messages on screen
#define STRATEGIX_DEBUG_EXCEPTION // Show exception message in log


//TODO: use something good for logging

namespace Strategix
{
class Log : public StrategixSingleton<Log>
{
public:
	Log();
	void Write(const char* time, const char* level, const char* file, int line, std::string message, int tabs = 0);
};
}

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

#endif    /* _STRATEGIXLOG_H */

