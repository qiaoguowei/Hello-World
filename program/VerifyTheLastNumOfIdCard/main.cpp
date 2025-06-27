#include <iostream>
#include <array>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    array<int, 17> verifyNum = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    array<int, 11> resultNum = {1, 0, 88, 9, 8, 7, 6, 5, 4, 3, 2};

    string idCard(argv[1]);
    if (idCard.size() != 17)
    {
        std::cout << "Enter 17 digits" << endl;
        return -1;
    }

    int sum = 0;
    for (int i = 0; i < 17; i++)
    {
        sum += (int)(idCard[i] - '0')  * verifyNum[i];
    }
    sum %= 11;
    std::cout << resultNum[sum] << endl;
}
