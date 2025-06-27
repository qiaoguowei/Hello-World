#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    try
    {
        shared_ptr<string> sp(new string("hi"));
        weak_ptr<string> wp = sp;
        sp.reset();
        cout << wp.use_count() << endl;
        cout << boolalpha << wp.expired() << endl;
        shared_ptr<string> p(wp);
    }
    catch (const std::exception& e)
    {
        cerr << "exception: " << e.what() << endl;
    }
}
