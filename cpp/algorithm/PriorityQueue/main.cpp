#include <iostream>
#include "priority_queue.h"

int main()
{
    // 默认大根堆测试
    PriorityQueue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);

    std::cout << "Max heap: ";
    while (!maxHeap.empty())
    {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << "\n";

    // 小根堆测试
    PriorityQueue<int, std::vector<int>, std::greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(5);

    std::cout << "Min heap: ";
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << "\n";

    return 0;
}
