#include <iostream>
#include <functional>
#include <cstdio>
#include <unistd.h>
#include <sys/file.h>
#include <boost/thread.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

void thr_f1(int fd)
{
	if (flock(fd, LOCK_EX))
	{
		cout << "flock failed." << endl;
		return;
	}

	string oldfile = "./111";
	string newfile = "./333";
	if (!rename(oldfile.c_str(), newfile.c_str()))
	{
		cout << "rename success." << endl;
		sleep(30);
		flock(fd, LOCK_UN);
		return ;
	}
	cout << "rename failed" << endl;
	flock(fd, LOCK_UN);
}

void thr_f2(int fd)
{
	if (flock(fd, LOCK_EX))
	{
		cout << "flock failed." << endl;
		return;
	}

	string oldfile = "./222";
	string newfile = "./333";
	if (!rename(oldfile.c_str(), newfile.c_str()))
	{
		cout << "rename success." << endl;
		sleep(30);
		flock(fd, LOCK_UN);
		return ;
	}
	cout << "rename failed" << endl;
	flock(fd, LOCK_UN);
}

int main()
{
	int fd = open("./333", O_RDONLY);
	if (fd < 0)
	{
		cout << "open file failed." << endl;
		return -1;
	}

	boost::thread t1(std::bind(thr_f1, std::ref(fd)));
	boost::thread t2(std::bind(thr_f2, std::ref(fd)));

	t1.join();
	t2.join();
	close(fd);
}











