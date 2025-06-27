#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include <sys/time.h>

// char *strptime(const char *s, const char *format, struct tm *tm);
int main()
{
	std::string str1 = "2025-03-07T04:24:23Z";
	std::string str_format = "%Y-%m-%dT%H:%M:%SZ";
	char *rtn = NULL;
	struct tm m_tm;
	memset(&m_tm, 0, sizeof(m_tm));

	rtn = strptime(str1.c_str(), str_format.c_str(), &m_tm);
	if(rtn == NULL)
	{
		std::cout << "strptime() error." << std::endl;
		return -1;
	}
	std::cout << m_tm.tm_yday << std::endl;

	time_t m_time = ::mktime(&m_tm);
	if(m_time == -1)
	{
		std::cout << "mktime() error." << std::endl;
		return -1;
	}

	std::cout << m_time << std::endl;

	//int gettimeofday(struct timeval *tv, struct timezone *tz);
	struct timeval m_tv;
	if(gettimeofday(&m_tv, 0) != 0)
	{
		std::cout << "gettimeofday() error." << std::endl;
		return -1;
	}

	std::cout << m_tv.tv_sec << std::endl;
}
