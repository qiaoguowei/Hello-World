#include <iostream>

int main()
{
    std::string line_char;

    getline(std::cin, line_char);
    int64_t result = 0;
    size_t size_line = line_char.size();
    std::cout << size_line << std::endl;
    for (int i = 0; i < size_line; ++i)
    {
        if (line_char[size_line - i - 1] == ' ')
        {
            result = i;
            break;
        }
    }
    std::cout << result << std::endl;
}
