#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <string>

struct ScheduleInfo
{
	bool enabled;
	std::string validDays;
	std::string beginTimes;
	std::string rangeBegin;
	std::string rangeEnd;
	std::string desc;
	int intervalSeconds;
};


#endif

