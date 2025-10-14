#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> cities;
    cities["beijing"] = 0;
    cities["shanghai"] = 1;
    cities["shenzhen"] = 2;
    cities["guangzhou"] = 3;

    for (const auto& [cityName, cityNumber] : cities)
    {
        std::cout << cityName << ": " << cityNumber << std::endl;
    }
}
