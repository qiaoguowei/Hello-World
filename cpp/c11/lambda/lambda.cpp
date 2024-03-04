#include <iostream>

using namespace std;

void test1()
{
    int id = 0;
    auto f = [&id]() {
        cout << "id: " << id << endl;
        ++id;
    };

    f();
    f();
    cout << id << endl;
    id = 42;
    f();
    cout << id << endl;
}

void test2()
{
    int id = 0;
    auto f = [id]() mutable {
        cout << "id: " << id << endl;
        ++id;
    };

    f();
    f();
    cout << id << endl;
    id = 42;
    f();
    cout << id << endl;
}

int main()
{
    test2();
}





