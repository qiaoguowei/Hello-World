#include <iostream>
#include <time.h>
#include <cstring>
#include <sys/time.h>

std::string gf_time()
{
    struct timeval tv;
    char str[30] = {0};
    char *ptr = nullptr;

    if (gettimeofday(&tv, NULL) < 0)
    {
        std::cout << "gettimeofday error." << std::endl;
        return std::string();
    }

    ptr = ctime(&tv.tv_sec);
    strncpy(str, ptr, sizeof(str) - 1);

    snprintf(str + 19, sizeof(str) - 20, ".%06ld", tv.tv_usec);

    return std::string(str);
}

int main()
{
    std::string date_str = gf_time();
    std::cout << date_str << std::endl;
}
