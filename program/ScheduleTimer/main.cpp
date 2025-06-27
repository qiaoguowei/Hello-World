#include <iostream>
#include <unistd.h>
#include "ScheduleTimer.h"
#include "common.h"
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <functional>

bool print()
{
	std::cout << "1111111111" << std::endl;
	return true;
}

int main()
{
	ScheduleInfo mScheduleInfo;
	mScheduleInfo.validDays = "0,1,2,3,4,5,6";
	mScheduleInfo.rangeBegin = "1:00";
	mScheduleInfo.rangeEnd = "23:00";
	mScheduleInfo.intervalSeconds = 5;
	mScheduleInfo.desc = "schedule test";

	auto f = []()
	{
		std::cout << "11111111111" << std::endl;
	};
	std::function<bool()> ff = print;

	boost::shared_ptr<ScheduleTimer> st(new ScheduleTimer(mScheduleInfo, ff)); 
	st->start();
	sleep(10000);	
}
