#include <iostream>
#include <string>

int main()
{
    std::string mLastLocationID = "/0_0/1_1";
    std::string fullLocationID = "/0_0/1_2";

    int lastLocationIDPrefix = mLastLocationID.rfind("_");
    int fullLocationIDPrefix = fullLocationID.rfind("_");

    std::cout << "lastLocationIDPrefix is " << lastLocationIDPrefix << std::endl;
    std::cout << "fullLocationIDPrefix is " << fullLocationIDPrefix << std::endl;
}
