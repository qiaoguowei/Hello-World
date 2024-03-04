#include <iostream>
#include <stdlib.h>

int main()
{
    //int status = system("ls");
    int status = system("xxx");
    status = WEXITSTATUS(status);

    std::cout << status << std::endl;
}
