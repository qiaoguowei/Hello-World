#include <iostream>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/concurrency/TimerManager.h>
#include <memory>
#include <chrono>
#include <thrift/concurrency/Monitor.h>

namespace thrift = apache::thrift::concurrency;
using namespace std;

class MyTask : public thrift::Runnable
{
public:
	MyTask() = default;
	~MyTask() override = default;
	void run() override
	{
		cout << "calling MyTask::run()." << endl;	
	}
};

int main()
{
	std::shared_ptr<thrift::TimerManager> mTimerManager(new thrift::TimerManager());
	std::shared_ptr<thrift::ThreadFactory> mThreadFactory(new thrift::ThreadFactory(false));
	std::shared_ptr<MyTask> mTask(new MyTask);
	std::shared_ptr<thrift::Monitor> monitor_(new thrift::Monitor());
	mTimerManager->threadFactory(mThreadFactory);
	mTimerManager->start();
	mTimerManager->add(mTask, std::chrono::milliseconds(3000));
	monitor_->waitForTimeRelative(std::chrono::milliseconds(5000));
	mTimerManager->stop();
}



