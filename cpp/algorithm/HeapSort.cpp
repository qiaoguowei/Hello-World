#include <iostream>
#include <algorithm>

void maxHeapify(int arr[], int start, int end)
{
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1; //父节点的两个子节点为2n+1和2n+2

    while (son <= end) //子节点指标在范围内才做比较
    {
        if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点大小选择最大的
            son++;
        if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完毕，直接跳出函数
            return;
        else //否则交换父子内容再继续子节点和孙子节点比较
        {
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heapSort(int arr[], int len)
{
    //初始化，i从最后一个父节点开始调整
    for (int i = len / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, i, len - 1);
    }
    //先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
    for (int i = len - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        maxHeapify(arr, 0, i - 1);
    }
}

int main()
{
    int arr[] = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    heapSort(arr, len);
    for (int i = 0; i < len; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    return 0;
}











