#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
boost::mutex m_mutex;
void thread_handler()
{
	int i = 0;
	for(i; i < 100; ++i)
	{
		cout << 111 << endl;
		m_mutex.lock();
		cout << "thread_handler : " << i << endl;
		m_mutex.unlock();
		cout << 222 << endl;
		//boost::this_thread::sleep(boost::posix_time::seconds(1));
		cout << 333 << endl;
		if(i == 30)
		{
			boost::this_thread::interruption_point();
		}
	}
}

int main()
{
	boost::thread m_thread(&thread_handler);

	m_thread.interrupt();
	m_thread.join();
}
