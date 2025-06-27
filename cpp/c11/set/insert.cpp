#include <iostream>
#include <set>

int main()
{
    std::set<int> num_set;
    std::pair<std::set<int>::iterator, bool> insert_result = num_set.insert(1);
    if (insert_result.second)
    {
        std::cout << __LINE__ << " insert 1 success." << std::endl;
    }
    else
    {
        std::cout << __LINE__ << " insert 1 failed." << std::endl;
    }

    std::pair<std::set<int>::iterator, bool> insert_result2 = num_set.insert(1);
    if (insert_result2.second)
    {
        std::cout << __LINE__ << " insert 1 success." << std::endl;
    }
    else
    {
        std::cout << __LINE__ << " insert 1 failed." << std::endl;
    }
}
