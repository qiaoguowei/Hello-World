#include <iostream>
#include <string>
#include <vector>
#include "item22.h"

struct Widget::Impl
{
    std::string name;
    std::vector<double> data;
};

Widget::Widget()
    : pImpl(std::make_unique<Impl>())
{
}

int main()
{
    Widget w;
}
