#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

/*
 * 产生随机数的办法是，将引擎dre分别与两个分布di和dr组合起来：
 * 引擎作为随机性的源头。它们是function object，能够产生随机的无正负值，并均匀分布于一个预定义的最小和最大值之间。
 * 分布表示以何种手法，将这些随机值（random value）转换为随机数（random number），后者分布于一个由使用者给定的参数所决定的区间内。
 * */

int main()
{
    std::default_random_engine dre; //create default engine as source of randomness

    //use engine to generate integral numbers between 10 and 20(both include)
    std::uniform_int_distribution<int> di(10, 20);
    for (int i = 0; i < 20; ++i)
    {
        cout << di(dre) << " ";
    }
    cout << endl;

    //use engine to generate floatint-point numbers between 10.0 and 20.0
    //(10.0 include, 20.0 not include)
    std::uniform_real_distribution<double> dr(10.0, 20.0);
    for (int i = 0; i < 8; ++i)
    {
        cout << dr(dre) << " ";
    }
    cout << endl;

    //use engine to shuffle elements (shuffle 打乱顺序)
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(v.begin(), v.end(), dre);
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

//首先使用 uniform_int_distribution，它会产生整数。这些数的类型必须是以下之一：short、int、long、long long 及其相应的unsigned 类型。如果没有指定类型，默认是 int。构造函数的第一实参指出最小值（默认为 0），第二实参指出最大值（默认为numeric_limits＜type＞：：max（）,请注意最小值和最大值都可被生成出来，所以这不是个半开区间

//相同做法可作用于随机浮点数身上。然而请注意，此时传入的最小和最大值是个半开区间（half-open range），默认为[0.0，1.0）。可能的类型包括float、double（默认）或long double。下面的语句定义了一个分布 dr，生成的随机数介于10.0和 20.0之间（不含后者）：




