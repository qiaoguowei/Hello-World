#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool myfn(int i, int j) { return i<j; }

struct myclass {
      bool operator() (int i,int j) { return i<j; }
} myobj;

int test ()
{
      int myints[] = {3,7,2,5,6,4,9};

      //using default comparison:
          std::cout << "The smallest element is " << *std::min_element(myints,myints+7) << '\n';
      std::cout << "The largest element is "  << *std::max_element(myints,myints+7) << '\n';

      // using function myfn as comp:
      std::cout << "The smallest element is " << *std::min_element(myints,myints+7,myfn) << '\n';
      std::cout << "The largest element is "  << *std::max_element(myints,myints+7,myfn) << '\n';

      // using object myobj as comp:
      std::cout << "The smallest element is " << *std::min_element(myints,myints+7,myobj) << '\n';
      std::cout << "The largest element is "  << *std::max_element(myints,myints+7,myobj) << '\n';

      return 0;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 10, 0};

    int max_id = *std::max_element(nums.begin(), nums.end());
    int min_id = *std::min_element(nums.begin(), nums.end());

    cout << "max_id = " << max_id << endl;
    cout << "min_id = " << min_id << endl;
    test();
}



