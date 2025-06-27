#include <iostream>
#include <list>

using namespace std;

std::list<int> selectSort(std::list<int>& m_list)
{
    std::list<int> new_list;
    int list_size = m_list.size();
    for (int i = 0; i < list_size; ++i)
    {
        std::list<int>::iterator max = m_list.begin();
        for (std::list<int>::iterator iter = m_list.begin(); iter != m_list.end(); ++iter)
        {
            if (*max < *iter)
                max = iter;
        }
        new_list.push_back(*max);
        m_list.erase(max);
    }
    return new_list;
}

int main()
{
    std::list<int> m_list = {1, 3, 5, 7, 9, 2, 4, 6, 8};

    std::list<int> new_list = selectSort(m_list);
    for (auto& x : new_list)
    {
        cout << x << ", ";
    }
    cout << endl;
}
