#include <iostream>

int main()
{
    int weight_array[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    std::cout << sizeof(weight_array) / sizeof(int) << std::endl;

    std::string identify_card_str = "360502199905107116";
    int sum = 0;
    for (int i = 0; i < identify_card_str.size() - 1; ++i)
    {
        sum += ((identify_card_str[i] - '0') * weight_array[i]);
    }

    std::cout << "sum = " << sum << std::endl;
    int remainder = sum % 11;
    std::cout << "remainder = " << remainder << std::endl;

    char check_code_array[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
    std::cout << "the last number is " << check_code_array[remainder] << std::endl;
}
