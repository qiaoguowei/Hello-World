#include <iostream>
#include <string>
#include <map>


int main()
{
    std::map<std::string, int> cities;
    cities["beijing"] = 0;
    cities["shanghai"] = 1;
    cities["shenzhen"] = 2;
    cities["guangzhou"] = 3;

    std::pair<std::map<std::string, int>::iterator, int> insertResult = cities.insert(std::pair<std::string, int>("shanghai", 2));

    std::cout << "Is insertion successful ? " << (insertResult.second ? "true" : "false") << ", element key: " << insertResult.first->first << ", value: " << insertResult.first->second << std::endl;
}
