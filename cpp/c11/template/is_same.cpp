//is_same example
#include <iostream>
#include <type_traits>
#include <cstdint>

/*
 * template <class T, class U> struct is_same;
 * 标识T是否与U相同类型的特征类，包括具有相同的const和/或volatile限定条件(如果有的话)。
 *
 *
 * */

typedef int integer_type;
struct A
{
    int x,y;
};
struct B
{
    int x,y;
};

typedef A C;

int main()
{
    std::cout << std::boolalpha;
    std::cout << "is_same:" << std::endl;
    std::cout << "int, const int: " << std::is_same<int, const int>::value << std::endl;
    std::cout << "int, integer_type: " << std::is_same<int, integer_type>::value << std::endl;
    std::cout << "A, B: " << std::is_same<A,B>::value << std::endl;
    std::cout << "A, C: " << std::is_same<A,C>::value << std::endl;
    std::cout << "signed char, std::int8_t: " << std::is_same<signed char,std::int8_t>::value << std::endl;
    return 0;
}
