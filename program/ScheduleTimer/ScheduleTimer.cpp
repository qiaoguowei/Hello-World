#include "ScheduleTimer.h"
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;

#define MAKE_CALLBACK(func) boost::bind(&ScheduleTimer::func, this, boost::asio::placeholders::error)

boost::posix_time::ptime ScheduleTimer::epoch = boost::posix_time::ptime(boost::gregorian::date(1970, 1, 1));

ScheduleTimer::ScheduleTimer(const ScheduleInfo& info, std::function<bool()>& callback)
	: mScheduleInfo(info), 
	mCallback(callback),
	mThread(NULL),
	mValidDays(0),
	mIsStarted(false),
	mIsRunEnd(true)
{
}

ScheduleTimer::~ScheduleTimer()
{
	cout << "~ScheduleTimer()" << endl;
	if(mIsStarted)
		stop();
}

bool ScheduleTimer::start()
{
	cout << "ScheduleTimer::start()" << endl;
	if(!processScheduleSetting())
	{
		cout << "error: start() failed to process schedule settings" << endl;
		return false;
	}

	mThread.reset(new boost::thread(boost::bind(&ScheduleTimer::threadFunc, this)));
	mIsStarted = true;

	return true;
}

bool ScheduleTimer::stop()
{
	cout << "ScheduleTimer::stop() begin " << endl;
	if(mIsStarted && mTimer)
	{
		mIsStarted = false;
		mTimer->cancel();
		while(!mIsRunEnd)
			usleep(10);
		cout << "ScheduleTimer::stop(), delete timer." << endl;
		delete mTimer;
		mTimer = NULL;
	}
	cout << "ScheduleTimer::stop() end." << endl;
	return true;
}

void ScheduleTimer::threadFunc()
{
	mIsRunEnd = false;
	boost::asio::io_service io;
	boost::posix_time::ptime local_time = generateNextTimeoutPoint();
	//mNextTimeoutPoint = localToUTC(local_time);
	mNextTimeoutPoint = local_time;
	if(mNextTimeoutPoint.is_not_a_date_time())
	{
		cout << "error: begin time is not a date time." << endl;
		return ;
	}

	cout << mScheduleInfo.desc << ", threadFunc set begin time:" << local_time << endl;
	mTimer = new boost::asio::deadline_timer(io, mNextTimeoutPoint);
	mTimer->async_wait(MAKE_CALLBACK(timeout));

	io.run();
	mIsRunEnd = true;
	cout << "threadFunc() end." << endl;
}

void ScheduleTimer::timeout(const boost::system::error_code &ec)
{
	if(ec == boost::asio::error::operation_aborted)
	{
		cout << "timeout operation_aborted." << endl;
		return ;
	}

	mCallback();

	if(!mIsStarted)
		return ;

	::sleep(2);
	if(!mIsStarted)
		return ;

	boost::posix_time::ptime local_time = generateNextTimeoutPoint();
	//mNextTimeoutPoint = localToUTC(local_time);
	mNextTimeoutPoint = local_time;
	cout << "set next schedule time: " << local_time << endl;
	if(mNextTimeoutPoint.is_not_a_date_time())
	{
		cout << "begind time is not a date time." << endl;
		return;
	}

	mTimer->expires_at(mNextTimeoutPoint);
	mTimer->async_wait(MAKE_CALLBACK(timeout));
}

bool ScheduleTimer::processScheduleSetting()
{
	mValidDays = 0;
	std::vector<std::string> day_vec;
	boost::split(day_vec, mScheduleInfo.validDays, boost::is_any_of(","));
	for(const std::string &day : day_vec)
	{
		int day_num = atoi(day.c_str());
		if(day_num >= 0 && day_num <= 6)
			mValidDays |= (0x01 << day_num);
		else
			return false;
	}

	if(mValidDays == 0)
	{
		cout << "processScheduleSetting() invalid day of week" << endl;
		return false;
	}

	mBeginTimes.clear();
	std::vector<std::string> time_vec;
	if(!mScheduleInfo.beginTimes.empty())
	{
		boost::split(time_vec, mScheduleInfo.beginTimes, boost::is_any_of(","));
		for(const std::string &time : time_vec)
		{
			mBeginTimes.push_back(boost::posix_time::duration_from_string(time));
		}
	}
	else if(!mScheduleInfo.rangeBegin.empty() && !mScheduleInfo.rangeEnd.empty() && 
		mScheduleInfo.intervalSeconds > 0)
	{
		boost::posix_time::time_duration tmp = boost::posix_time::duration_from_string(mScheduleInfo.rangeBegin);
		boost::posix_time::time_duration end = boost::posix_time::duration_from_string(mScheduleInfo.rangeEnd);
		while(tmp < end)
		{
			mBeginTimes.push_back(tmp);
			tmp += boost::posix_time::time_duration(0, 0, mScheduleInfo.intervalSeconds);
		}
	}
	else
		return false;
	
	if(mBeginTimes.empty())
		cout << "invalid begin times." << endl;
	return !mBeginTimes.empty();
}

bool ScheduleTimer::isExecuteDay(unsigned int weekday)
{
	if(weekday <= 6)
		return mValidDays & (0x01 << weekday);
	else
		return false;
}

int ScheduleTimer::getNextExecuteDay(unsigned int today, unsigned int *days_after)
{
	unsigned int i, counter = 0;
	bool find = false;

	for(i = today + 1; i <= 6; ++i)
	{
		++counter;
		if(mValidDays & (0x01 << i))
		{
			find = true;
			break;
		}
	}

	if(!find)
	{
		for(i = 0; i <= today; ++i)
		{
			++counter;
			if(mValidDays & (0x01 << i))
			{
				find = true;
				break;
			}
		}
	}

	if(find)
	{
		if(days_after)
			*days_after = counter;
		return i;
	}
	else
	{
		if(days_after)
			*days_after = 0;
		return -1;
	}
}

boost::posix_time::time_duration ScheduleTimer::getBeginTime(const boost::posix_time::time_duration& now)
{
	for(const boost::posix_time::time_duration& time : mBeginTimes)
	{
		if(now > time)
			continue;
		else
			return time;
	}

	return boost::posix_time::not_a_date_time;
}

boost::posix_time::ptime ScheduleTimer::generateNextTimeoutPoint()
{
	boost::posix_time::ptime pt_now = boost::posix_time::second_clock::local_time();

	boost::posix_time::time_duration time_of_today = pt_now.time_of_day();
	int weekday = pt_now.date().day_of_week();
	if(isExecuteDay(weekday))
	{
		boost::posix_time::time_duration  begin_time = getBeginTime(time_of_today);
		if(begin_time.is_not_a_date_time())
		{
			unsigned int days_after = 0;
			if(getNextExecuteDay(weekday, &days_after) < 0)
				return boost::posix_time::ptime(boost::posix_time::not_a_date_time);

			pt_now = pt_now - time_of_today + boost::posix_time::hours(days_after * 24) + mBeginTimes.front();
		}
		else
		{
			pt_now = pt_now - time_of_today + begin_time;
		}
	}
	else
	{
		unsigned int days_after = 0;
		if(getNextExecuteDay(weekday, &days_after) < 0)
			return boost::posix_time::ptime(boost::posix_time::not_a_date_time);

		pt_now = pt_now - time_of_today + boost::posix_time::hours(days_after * 24) + mBeginTimes.front();
	}

	return pt_now;
}

boost::posix_time::ptime ScheduleTimer::getNextTimeoutPoint()
{
	return mNextTimeoutPoint;
}

boost::posix_time::ptime ScheduleTimer::localToUTC(const boost::posix_time::ptime& local_time)
{
	//boost::posix_time::ptime epoch_local = boost::date_time::c_local_adjustor<boost::posix_time::ptime>::utc_to_local(epoch);
	//return local_time - (epoch_local - epoch);
	return boost::posix_time::ptime();
}








