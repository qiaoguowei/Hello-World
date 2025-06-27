#ifndef _SCHEDULETIMER_H
#define _SCHEDULETIMER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include "common.h"


class ScheduleTimer
{
public:
	ScheduleTimer(const ScheduleInfo& info, std::function<bool()>& callback);
	~ScheduleTimer();

	bool start();
	bool stop();

	bool isExecuteDay(unsigned int weekday);
	boost::posix_time::ptime getNextTimeoutPoint();

private:
	void threadFunc();
	void timeout(const boost::system::error_code& ec);

	bool processScheduleSetting();

	boost::posix_time::time_duration getBeginTime(const boost::posix_time::time_duration& now);
	int getNextExecuteDay(unsigned int today, unsigned int *days_after = NULL);
	boost::posix_time::ptime generateNextTimeoutPoint();
	boost::posix_time::ptime localToUTC(const boost::posix_time::ptime& local_time);

	ScheduleInfo mScheduleInfo;
	boost::shared_ptr<boost::thread> mThread;
	boost::asio::deadline_timer *mTimer;
	std::function<bool()> mCallback;
	std::vector<boost::posix_time::time_duration> mBeginTimes;
	boost::posix_time::ptime mNextTimeoutPoint;
	uint8_t mValidDays;
	bool mIsStarted;
	bool mIsRunEnd;

	static boost::posix_time::ptime epoch;
};



#endif

