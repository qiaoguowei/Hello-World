#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main()
{
    bitset<8> mbit("11111111");
    uint64_t num = mbit.to_ullong();

    cout << num << endl;
    num &= ~3;

    cout << num << endl;
}
