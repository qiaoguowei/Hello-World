#include <thread>
#include <iostream>
#include <string>

using namespace std;

void thread_cb()
{
    cout << this_thread::get_id() << endl;
    cout << "there is the thread callback." << endl;
}

int main()
{
    cout << this_thread::get_id() << endl;
    cout << "there is the main function." << endl;
    thread mThread(thread_cb);

    mThread.join();
    return 0;
}
