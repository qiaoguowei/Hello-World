#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    std::vector<int> possible = {1, 2, 3, 4, 5};
    int tol = std::accumulate(possible.begin(), possible.end(), 0);
    std::cout << "total : " << tol << std::endl;

    int tol2 = std::accumulate(possible.begin(), possible.end(), 1);
    std::cout << "total2 : " << tol2 << std::endl;

    auto dash_fold = [](std::string a, int b)
    {
        return std::move(a) + '-' + std::to_string(b);
    };

    std::string s = std::accumulate(std::next(possible.begin()), possible.end(),
                                    std::to_string(possible[0]), // start with first element
                                    dash_fold);
    std::cout << "s = " << s << std::endl;

    std::string rs = std::accumulate(std::next(possible.rbegin()), possible.rend(),
                                     std::to_string(possible.back()), // start with last element
                                     dash_fold);
    std::cout << "rs = " << rs << std::endl;
}
