#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <functional>

template <typename T, typename Container = std::vector<T>,
         typename Compare = std::less<typename Container::value_type>>
class PriorityQueue
{
public:
    //默认构造函数
    PriorityQueue() = default;

    //迭代器范围构造函数
    template<typename InputIterator>
    PriorityQueue(InputIterator first, InputIterator last)
        : container_(first, last)
    {
        heapify();
    }

    // 插入元素
    void push(const T& value)
    {
        container_.push_back(value);
        siftUp(container_.size() - 1);
    }

    // 弹出队首元素
    void pop()
    {
        if (empty())
            return;
        std::swap(container_[0], container_.back());
        container_.pop_back();
        siftDown(0);
    }

    // 访问队首元素
    const T& top() const
    {
        return container_.front();
    }

    // 队列是否为空
    bool empty() const
    {
        return container_.empty();
    }

    // 队列元素数量
    size_t size() const
    {
        return container_.size();
    }

private:
    Container container_;
    Compare comp_;

    // 堆化操作
    void heapify()
    {
        for (int i = (container_.size() / 2) - 1; i >= 0; --i)
        {
            siftDown(i);
        }
    }

    // 上浮操作
    void siftUp(size_t index)
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (!comp_(container_[parent], container_[index]))
                break;
            std::swap(container_[parent], container_[index]);
            index = parent;
        }
    }

    // 下沉操作
    void siftDown(size_t index)
    {
        size_t last = container_.size();
        while (true)
        {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;

            if (left < last && comp_(container_[largest], container_[left]))
            {
                largest = left;
            }
            if (right < last && comp_(container_[largest], container_[right]))
            {
                largest = right;
            }
            if (largest == index)
                break;

            std::swap(container_[index], container_[largest]);
            index = largest;
        }
    }
};


#endif //PRIORITY_QUEUE_H
