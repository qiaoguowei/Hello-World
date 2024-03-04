#include <iostream>
#include <string>

using namespace std;

int main()
{
    uint64_t num = 0x1234567890123456;

    uint64_t ret = (num >> 32) % 0x1000;

    cout << std::hex << num << endl;
    cout << std::hex << ret << endl;
}
