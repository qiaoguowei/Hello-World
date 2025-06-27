#include <iostream>

int goingUpTheSteps(int numbers_of_steps)
{
    if (numbers_of_steps == 1)
        return 1;
    else if (numbers_of_steps == 2)
        return 2;
    else
        return goingUpTheSteps(numbers_of_steps - 1) + goingUpTheSteps(numbers_of_steps - 2);
}

int main()
{
    std::cout << goingUpTheSteps(20) << std::endl;
}
