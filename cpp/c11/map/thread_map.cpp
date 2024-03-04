#include <iostream>
#include <functional>
#include <map>
#include <thread>
#include <string>

using namespace std;

void thread_cb(map<int, string>& mm)
{
    for (auto& x : mm)
    {
        cout << x.first << ", " << x.second << endl;
    }
}

int main()
{
    map<int, string> mm;

    mm.insert(make_pair(111, "aaa"));
    mm.insert(make_pair(222, "bbb"));
    mm.insert(make_pair(333, "ccc"));
    mm.insert(make_pair(444, "ddd"));
    mm.insert(make_pair(555, "eee"));
    mm.insert(make_pair(666, "fff"));
    mm.insert(make_pair(777, "ggg"));
    mm.insert(make_pair(888, "hhh"));
    mm.insert(make_pair(999, "iii"));
    mm.insert(make_pair(100, "jjj"));

    thread th1(std::bind(thread_cb, std::ref(mm)));
    thread th2(std::bind(thread_cb, std::ref(mm)));
    thread th3(std::bind(thread_cb, std::ref(mm)));
    thread th4(std::bind(thread_cb, std::ref(mm)));
    thread th5(std::bind(thread_cb, std::ref(mm)));

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    return 0;
}

















