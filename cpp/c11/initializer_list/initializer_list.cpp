#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

/*
 * std：：initializer_list<T>除了提供了构造函数，还提供了三个成员函数，这和 stl其他容器的同名方法用法一样
 * size_type size() const;
 * const T* begin() const;
 * const T* end() const;
 * */

class A
{
public:
    A(std::initializer_list<int> integers)
    {
        m_vecIntegers.insert(m_vecIntegers.end(), integers.begin(), integers.end());
    }

    ~A()
    {
    }

    void append(std::initializer_list<int> integers)
    {
        m_vecIntegers.insert(m_vecIntegers.end(), integers.begin(), integers.end());
    }

    void print()
    {
        for (auto& x : m_vecIntegers)
        {
            cout << x << endl;
        }
    }

private:
    std::vector<int> m_vecIntegers;
};

int main()
{
    A a{1, 2, 3};
    a.print();

    cout << "After appending..." << endl;
    a.append({4, 5, 6});
    a.print();

    return 0;
}











