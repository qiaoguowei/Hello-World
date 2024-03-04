#include <iostream>
#include <vector>

class Solution
{
public:
    bool carPooling(std::vector<std::vector<int>> &trips, int capacity)
    {
#if 0
        std::pair<int, int> the_first_to = std::make_pair(0, trips[0][2]);
        int temp_capacity = trips[0][0];
        int max_capacity = trips[0][0];
        for (int i = 1; i < trips.size();)
        {
            if (trips[i][1] >= the_first_to.second)
            {
                if (temp_capacity > max_capacity)
                    max_capacity = temp_capacity;
                temp_capacity -= trips[the_first_to.first][0];
                the_first_to.first = the_first_to.first + 1;
                the_first_to.second = trips[the_first_to.first][2];
            }
            else
            {
                temp_capacity += trips[i][0];
                i++;
            }

            if (i == the_first_to.first)
            {
                temp_capacity += trips[i][0];
                i++;
            }
        }

        if (temp_capacity > max_capacity)
            max_capacity = temp_capacity;

        std::cout << max_capacity << std::endl;
        return true;
#else
        int to_max = 0;
        for (const auto& trip: trips)
        {
            to_max = max(to_max, trip[2]);
        }

        vector<int> diff(to_max + 1);
        for (const auto& trip: trips)
        {
            diff[trip[1]] += trip[0];
            diff[trip[2]] -= trip[0];
        }

        int count = 0;
        for (int i = 0; i <= to_max; ++i)
        {
            count += diff[i];
            if (count > capacity)
            {
                return false;
            }
        }
        return true;

#endif
    }
};

int main()
{
    std::vector<int> trip1 = {7,5,6};
    std::vector<int> trip2 = {6,7,8};
    std::vector<int> trip3 = {10,1,6};
    std::vector<int> trip4 = {4, 8, 9};
    std::vector<std::vector<int>> trips;
    trips.push_back(trip1);
    trips.push_back(trip2);
    trips.push_back(trip3);
    trips.push_back(trip4);
    Solution s;
    std::cout << s.carPooling(trips, 5) << std::endl;
}
