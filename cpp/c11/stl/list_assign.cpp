#include <iostream>
#include <string>
#include <list>

void test1()
{
    std::list<int> first;
    std::list<int> second;

    for (int i = 1; i < 10; i++)
    {
        first.push_back(i);
    }

<<<<<<< HEAD
    second.push_back(11);
    second.push_back(22);
    second.push_back(33);

=======
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
    second.assign(first.begin(), first.end());

    first.clear();
    for (auto &x : second)
    {
        std::cout << x << std::endl;
    }
}

void test2()
{
    std::list<char> characters;

    auto print_list = [&]()
    {
        for (const char& c : characters)
            std::cout << c << ' ';
        std::cout << '\n';
    };

    characters.assign(5, 'a');
    print_list();

    const std::string extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
    print_list();

    characters.assign({'C', '+', 'l', '1'});
    print_list();
}

int main()
{
<<<<<<< HEAD
    test1();
=======
    test2();
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
}







