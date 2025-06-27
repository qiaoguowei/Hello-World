//enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

/*
 * template <bool Cond, class T = void> struct enable_if;
 * 满足条件时启用类型
 *
 * 如果Cond为true，则启用类型T作为成员类型enable_if::type。
 *
 * 否则，没有定义enable_if::type。
 *
 * 这对于在编译时不满足特定条件时隐藏签名很有用，因为在这种情况下，成员enable_if::type将不会被定义，使用它进行编译应该会失败。
 *
 *
 * */

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i)
{
    return bool(i%2);
}

// 2. the second template argument is only valid if T is an integral type:
template < class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i)
{
    return !bool(i%2);
}

int main()
{
    //short int i = 1;    // code does not compile if type of i is not integral
    float i = 1.1;

    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    std::cout << "i is even: " << is_even(i) << std::endl;

    return 0;
}
