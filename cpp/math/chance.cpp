#include <iostream>
#include <vector>

void print_vector(std::vector<int>& vec)
{
    for (int& x : vec)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

void swap_num(int& a, int& b)
{
    int c;
    c = a;
    a = b;
    b = c;
}

void chance(std::vector<int> vec)
{
    std::vector<int> tmp_vec;
    tmp_vec.resize(vec.size());
    for (int a = 0; a < vec.size(); a++)
    {
        for (int b = 0; b < vec.size(); b++)
        {
            if (a == b)
                continue;
            for (int c = 0; c < vec.size(); c++)
            {
                if (c == a || c == b)
                    continue;
                for (int d = 0; d < vec.size(); d++)
                {
                    if (d == a || d == b || d == c)
                        continue;
                    for (int e = 0; e < vec.size(); e++)
                    {
                        if (e == a || e == b || e == c || e == d)
                            continue;
                        tmp_vec[0] = vec[a];
                        tmp_vec[1] = vec[b];
                        tmp_vec[2] = vec[c];
                        tmp_vec[3] = vec[d];
                        tmp_vec[4] = vec[e];
                        print_vector(tmp_vec);
                    }
                }
            }
        }
    }
}

void chance(std::vector<int>& vec, std::vector<int>& indexs)
{
    if (vec.size == indexs.size())
        return;

    for (int i = 0; i < vec.size(); ++i)
    {
        
    }
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    chance(vec);
}
