#include <iostream>
#include <thread>
#include <functional>
#include <utility>
#include <stdlib.h>

using namespace std;

void add(int a, int b)
{
    cout << std::this_thread::get_id() << endl;
    cout << a + b << endl;
}

template <typename _Fx, typename ... _Args>
void create(_Fx&& fx, _Args&&... args)
{
    std::thread m_thread(std::bind(std::forward<_Fx>(fx), std::forward<_Args>(args)...));

    m_thread.join();
}

int main(int argc, char *argv[])
{
    cout << std::this_thread::get_id() << endl;
    if (argc < 3)
    {
        cout << "example: ./a.out 4 5" << endl;
        return -1;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    create(add, a, b);
}
