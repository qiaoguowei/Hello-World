#include <time.h>
#include <iostream>

int main()
{
    uint64_t tt = time(NULL);
    std::cout << tt << std::endl;
}
