#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    char buffer[255] = {0};
    time_t rawtm;

    time(&rawtm);

    struct tm *timeinfo = localtime(&rawtm);

    strftime(buffer, 255, "%Y-%m-%d %H:%M:%S", timeinfo);
    cout << buffer << endl;
}
