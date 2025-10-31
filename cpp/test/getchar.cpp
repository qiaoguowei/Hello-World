#include <iostream>
#include <string>
#include <unordered_set>

void moveLeft(int& x, int move_num)
{
    x -= move_num;
}
void moveRight(int& x, int move_num)
{
    x += move_num;
}
void moveDown(int& y, int move_num)
{
    y -= move_num;
}
void moveUp(int& y, int move_num)
{
    y += move_num;
}

int main()
{
    int x = 0, y = 0;
    std::string line_char;
    std::cin >> line_char;

    std::string one_order;
    char instruct;
    int move_num = 0;
    std::string move_num_str;
    std::unordered_set<char> move_char({'A', 'S', 'D', 'W'});
    std::unordered_set<char> num_char({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    for (int i = 0; i < line_char.size(); ++i)
    {
        if (line_char[i] == ';')
        {
            move_num = atoi(move_num_str.c_str());
            move_num_str.clear();
            if (move_num > 0 && move_num < 100)
            {
                switch (instruct)
                {
                    case 'A':
                        moveLeft(x, move_num);
                        break;
                    case 'D':
                        moveRight(x, move_num);
                        break;
                    case 'S':
                        moveDown(y, move_num);
                        break;
                    case 'W':
                        moveUp(y, move_num);
                        break;
                }
            }
        }
        if (move_char.count(line_char[i]))
        {
            if (!move_num_str.empty())
            {
                move_num_str.clear();
                instruct = 0;
                continue;
            }
            instruct = line_char[i];
        }
        else if (num_char.count(line_char[i]))
        {
            move_num_str += line_char[i];
        }
        else
        {
            move_num_str.clear();
            instruct = 0;
        }
    }

    std::cout << x << ", " << y << std::endl;

}
