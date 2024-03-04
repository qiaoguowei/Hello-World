#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <boost/thread.hpp>
#include <functional>

using namespace std;

/*
 * struct flock
 * {
 *		short l_type;  锁定的状态 F_RDLCK, F_WRLCK, F_UNLCK
 *		以下的三个参数用于分段对文件加锁，若对整个文件加锁，则：l_whence=SEEK_SET, l_start=0, l_len=0
 *		short l_whence; 决定l_start位置 SEEK_SET, SEEK_CUR, SEEK_END
 *		off_t l_start;  Starting offset for lock
 *		off_t l_len;	Number of bytes to lock
 *
 *		pid_t l_pid;	PID of process blocking our lock(set by F_GETLK and F_OFD_GETLK)
 * };
 *
 * int fcntl(int fd, int cmd, struct flock *lock);
 * cmd F_SETLK 非阻塞
 *	   F_SETLKW 阻塞等待
 *     F_GETLK  获取锁的状态
 *
 * */

void thr_f1(int fd)
{
	struct flock m_lock;
	memset(&m_lock, 0, sizeof(struct flock));
	m_lock.l_type = F_WRLCK;
	m_lock.l_whence = SEEK_SET;
	m_lock.l_start = 0;
	m_lock.l_len = 0;

	while(1)
	{
		if (fcntl(fd, F_SETLKW, &m_lock) < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			cout << "fcntl set lock failed." << endl;
			return ;
		}
		break;
	}

	//string oldfile = "./111";
	//string newfile = "./333";

	//rename(oldfile.c_str(), newfile.c_str());
	cout << "rename success." << endl;
	sleep(10);
	m_lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &m_lock);
}

void thr_f2(int fd)
{
	sleep(2);

	struct flock m_lock;
	memset(&m_lock, 0, sizeof(struct flock));
	//m_lock.l_type = F_WRLCK;
	//m_lock.l_whence = SEEK_SET;
	//m_lock.l_start = 0;
	//m_lock.l_len = 0;

	while(1)
	{
		if (fcntl(fd, F_GETLK, &m_lock) < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			cout << "fcntl set lock failed." << endl;
			return ;
		}
		break;
	}
	cout << "getlock." << endl;

	if (m_lock.l_type == F_WRLCK)
	{
		cout << "the file is set write lock." << endl;
	}
	else if(m_lock.l_type == F_RDLCK)
	{
		cout << "the file is set read lock." << endl;
	}
	else
	{
		cout << "the file is not lock." << endl;
	}
}

int main()
{
	int fd = open("./333", O_RDWR);
	if (fd < 0)
	{
		cout << "open file failed." << endl;
		return -1;
	}

	boost::thread t1(std::bind(thr_f1, std::ref(fd)));
	boost::thread t2(std::bind(thr_f2, std::ref(fd)));
	//boost::thread t1(thr_f1);
	//boost::thread t2(thr_f2);

	t1.join();
	t1.join();
	close(fd);
}
