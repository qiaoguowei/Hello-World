#include <iostream>
#include <vector>

/*
比较相邻的元素，如果第一个比第二个大，就交换它们两个。
对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。这一步骤做完后，最后的元素会是最大的数。
针对所有的元素重复以上步骤，除了最后一个。
持续对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
 */

void bubble_sort(std::vector<int>& numeric_array)
{
    int array_size = numeric_array.size();
    for (int i = 0; i < array_size - 1; ++i)
    {
        for (int j = 0; j < array_size - 1 - i; ++j)
        {
            if (numeric_array[j] > numeric_array[j + 1])
            {
                int temp = numeric_array[j];
                numeric_array[j] = numeric_array[j + 1];
                numeric_array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    std::vector<int> numeric_array = {3, 9, -1, 10, 20};

    std::cout << "former array is [";
    for (const auto& x : numeric_array)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    bubble_sort(numeric_array);

    std::cout << "current array is [";
    for (const auto& x : numeric_array)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;
}









