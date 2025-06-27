#include <iostream>
#include <string>
#include <time.h>
#include <string.h>

using namespace std;

/*
 * int clock_gettime(clockid_t clk_id,struct timespec *tp);
 *
 * clk_id : 检索和设置的clk_id指定的时钟时间。
 *
 * CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,中间时刻如果系统时间被用户改成其他,则对应的时间相应改变。
 * CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响。
 * CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间。
 * CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间。
 *
 * */

int main()
{
	timespec time1;
	memset(&time1, 0, sizeof(time1));
	if (::clock_gettime(CLOCK_MONOTONIC, &time1) == -1)
	{
		perror("clock_gettime()");
		return -1;
	}

	cout << time1.tv_sec << ".";
	cout << time1.tv_nsec << endl;

	memset(&time1, 0, sizeof(time1));
	if (::clock_gettime(CLOCK_REALTIME, &time1) == -1)
	{
		perror("clock_gettime()");
		return -1;
	}
	cout << time1.tv_sec << ".";
	cout << time1.tv_nsec << endl;

	memset(&time1, 0, sizeof(time1));
	if (::clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1) == -1)
	{
		perror("clock_gettime()");
		return -1;
	}
	cout << time1.tv_sec << ".";
	cout << time1.tv_nsec << endl;

	memset(&time1, 0, sizeof(time1));
	if (::clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1) == -1)
	{
		perror("clock_gettime()");
		return -1;
	}
	cout << time1.tv_sec << ".";
	cout << time1.tv_nsec << endl;
}



















