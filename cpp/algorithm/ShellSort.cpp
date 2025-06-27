#include <iostream>
#include <vector>

void shell(std::vector<int>& numeric_array, int gap)
{
    //i下标从第一组的第二个数据开始
    for (int i = gap; i < numeric_array.size(); ++i)
    {
        int tmp = numeric_array[i];//tmp存放i下标的值
        int j = i - gap;//j下标为i-gap

        //j每次-gap个位置
        for (; j >= 0; j -= gap)
        {
            if (numeric_array[j] > tmp)
                numeric_array[j + gap] = numeric_array[j];
            else
                break;
        }
        numeric_array[j + gap] = tmp;
    }
}

void shellSort(std::vector<int>& numeric_array)
{
    int gap = numeric_array.size();
    while (gap > 1)
    {
        gap /= 2;
        shell(numeric_array, gap);
    }
}

int main()
{
    std::vector<int> numeric_array = {9, 1, 2, 5, 7, 4, 8, 6, 3, 5};

    std::cout << "former array is [";
    for (const auto& x : numeric_array)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;

    shellSort(numeric_array);

    std::cout << "current array is [";
    for (const auto& x : numeric_array)
    {
        std::cout << x << " ";
    }
    std::cout << "]" << std::endl;
}










