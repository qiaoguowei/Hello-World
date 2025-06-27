#include <iostream>
#include <queue>

#if 0
template <typename T>
class CompirePriority
{
public:
    bool operator() (std::pair<int, T> a, std::pair<int, T> b)
    {
        return a.first > b.first;
    }
};

int main()
{
    std::priority_queue<std::string, std::vector<std::pair<int, std::string>>, CompirePriority<std::string>> m_queue;
}
#endif

/*
   template<
       class T,
       class Container = std::vector<T>,
       class Compare = std::less<typename Container::value_type>
   > class priority_queue;

   T    -   存储元素的类型。T 与 Container::value_type 不是同一类型时非良构。

   Container    -   用于存储元素的底层容器类型。容器必须满足序列容器 (SequenceContainer) 的要求，并且它的迭代器必须满足老式随机访问迭代器 (LegacyRandomAccessIterator) 的要求。另外，它必须提供拥有通常语义的下列函数：
   back()，例如 std::vector::back()，
   push_back()，例如 std::deque::push_back()，
   pop_back()，例如 std::vector::pop_back()。
   标准容器 std::vector（包括 std::vector<bool>）和 std::deque 满足这些要求。

   Compare  -   提供严格弱序的比较 (Compare) 类型。
   注意比较 (Compare) 形参的定义，使得它的第一实参在弱序中 先于 它的第二实参时返回 true。但因为优先级队列首先输出最大元素，所以“先来”的元素实际上会在最后输出。即队列头含有按照比较 (Compare) 所施加弱序的“最后”元素。

    `priority_queue`的特点
    1. **自动排序**：队列中的元素自动按优先级排序，优先级高的元素总是位于队首。
    2. **插入和删除效率高**：插入元素和删除优先级最高的元素的时间复杂度为O(log n)。
    3. **只允许访问队首元素**：只能访问优先级最高的元素，即`top()`函数提供访问，而不允许随机访问其他元素。
    `priority_queue`的构造和用法
    1. 创建`priority_queue`，要使用`priority_queue`，你需要包含头文件 `<queue>`，并按照以下方式声明一个优先队列：
 */

void test1()
{
    std::priority_queue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(30);

    //获取队首元素（最大元素）
    std::cout << "队首元素（最大值）: " << pq.top() << std::endl;

    //移除对首元素
    pq.pop();
    std::cout << "移除后队首元素: " << pq.top() << std::endl;
}

void leastDeap()
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    //插入元素
    minHeap.push(10);
    minHeap.push(20);
    minHeap.push(30);

    //获取队首元素（最小元素）
    std::cout << "队首元素（最小值）: " << minHeap.top() << std::endl;
}

int main()
{
    leastDeap();
}





