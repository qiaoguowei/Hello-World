#include <iostream>
#include <semaphore.h>
#include <cstring>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: semunlink <name>" << std::endl;
        return -1;
    }

    if (sem_unlink(argv[1]))
    {
        std::cout << "sem_unlink() failed. Error message: " << strerror(errno) << std::endl;
        return -1;
    }

    return 0;
}
