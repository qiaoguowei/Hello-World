#include <iostream>
#include <algorithm>

template <class ForwardIt, class Compare>
constexpr ForwardIt is_sorted_until(ForwardIt first, ForwardIt last, Compare comp)
{
    if (first != last)
    {
        ForwardIt next = first;
        while (++next != last)
        {
            if (comp(*next, *first))
                return next;
            first = next;
        }
    }
    return last;
}

int main()
{
    const int N = 6;
    int nums[N] = {3, 1, 4, 1, 5, 9};

    const int min_sorted_size = 4;

    for (int sorted_size = 0; sorted_size < min_sorted_size; sorted_size++)
    {
        int *const sorted_end = std::is_sorted_until(nums, nums + N);
        std::cout << *sorted_end << std::endl;

        for (const auto i : nums)
            std::cout << i << ' ';
        std::cout << ": " << sorted_size << " initial sorted elements\n";
//            << std::string(sorted_size * 2 - 1, '^') << '\n';
    }
}




