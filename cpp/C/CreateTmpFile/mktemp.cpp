#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    char tempFile[1024] = {0};
    strncpy(tempFile, "unknownSubNameXXXXXX", sizeof(tempFile));
    cout << ::mktemp(tempFile) << endl;
    cout << tempFile << endl;
}
