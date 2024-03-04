#include <iostream>
#include <map>
#include <memory>

int main()
{
    std::shared_ptr<int> aa = std::make_shared<int>(1);

    std::cout << aa.use_count() << std::endl;
    std::map<int, std::shared_ptr<int>> mm;

    mm.insert(std::pair<int, std::shared_ptr<int>>(1, aa));
    std::cout << aa.use_count() << std::endl;

    mm.insert(std::pair<int, std::shared_ptr<int>>(2, aa));
    std::cout << aa.use_count() << std::endl;

    mm.insert(std::pair<int, std::shared_ptr<int>>(3, aa));
    std::cout << aa.use_count() << std::endl;

    mm[33] = aa;
    std::cout << aa.use_count() << std::endl;
    mm.clear();
    std::cout << aa.use_count() << std::endl;

    aa.reset();
    std::cout << aa.use_count() << std::endl;
}
