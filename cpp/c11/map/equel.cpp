#include <iostream>
#include <map>
#include <set>

int main()
{
    std::map<uint32_t, uint64_t> column_code1;
    std::map<uint32_t, uint64_t> column_code2;

    column_code1.insert(std::make_pair<uint32_t, uint64_t>(196609, 137909687613151474));
    column_code2.insert(std::make_pair<uint32_t, uint64_t>(196609, 137909687613151474));

    column_code1.insert(std::make_pair<uint32_t, uint64_t>(196610, 167572016562404043));
    column_code2.insert(std::make_pair<uint32_t, uint64_t>(196610, 167572016562404043));

    column_code1.insert(std::make_pair<uint32_t, uint64_t>(196611, 174846654330979893));
    column_code2.insert(std::make_pair<uint32_t, uint64_t>(196611, 174846654330979893));

    if (column_code1 == column_code2)
        std::cout << "equel" << std::endl;
    else
        std::cout << "no equel" << std::endl;
    std::set<std::map<uint32_t, uint64_t>> xxx;
    xxx.insert(column_code1);
    std::cout << xxx.size() << std::endl;
    xxx.insert(column_code2);
    std::cout << xxx.size() << std::endl;
}
