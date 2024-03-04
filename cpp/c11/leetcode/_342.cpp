#include <iostream>
#include <stdlib.h>

class Solution
{
public:
    bool isPowerOfFour(int n)
    {
        return n > 0 && (n & (n - 1)) == 0 && (n & 0xAAAAAAAA) == 0;
    }
};

int main(int argc, char *argv[])
{
    int n = 0;
    if (argc != 2)
    {
        std::cout << "argc is not equal 2, exit" << std::endl;
        return -1;
    }
    n = atoi(argv[1]);
    Solution s;
    bool ret = s.isPowerOfFour(n);

    std::cout << (ret ? "true" : "false") << std::endl;
}
