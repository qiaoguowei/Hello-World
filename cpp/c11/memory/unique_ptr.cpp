#if 1
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    std::unique_ptr<string> up(new std::string("nico"));

    std::string *sp = up.release(); //up lose ownership
    if (up == nullptr)
    {
        cout << "up lose owner ship" << endl;
    }
    cout << *sp << endl;
    delete sp;
}
#else
// unique_ptr::release example
#include <iostream>
#include <memory>

int main ()
{
    std::unique_ptr<int> auto_pointer (new int);
    int * manual_pointer;

    *auto_pointer=10;

    manual_pointer = auto_pointer.release();
    // (auto_pointer is now empty)

    std::cout << "manual_pointer points to " << *manual_pointer << '\n';

    delete manual_pointer;

    return 0;
}
#endif
