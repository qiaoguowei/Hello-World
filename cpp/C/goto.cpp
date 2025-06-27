#include <iostream>
#include <unistd.h>

int main()
{
    int a = 0;
retry:
    if (a < 3)
    {
        std::cout << "a = " << a << std::endl;
        a++;
        sleep(1);
        goto retry;
    }
}
