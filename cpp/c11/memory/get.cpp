#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> xxx = std::make_shared<int>(1);
    std::cout << xxx.use_count() << std::endl;

    uint64_t p = (uint64_t)xxx.get();
    std::cout << p << std::endl;
    std::cout << xxx.use_count() << std::endl;
}
