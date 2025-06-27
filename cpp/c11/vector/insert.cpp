#include <iostream>
#include <vector>
int main()
{
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};
    // 在vec1的末尾插入vec2的所有元素
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    // 输出结果
    for (int num : vec1)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}
