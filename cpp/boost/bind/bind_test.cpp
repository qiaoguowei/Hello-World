#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
//#include <functional>

using namespace std;

class Hello
{
public:
    void say(std::string& name)
    {
        cout << name << " say hello" << endl;
    }
};

int main()
{
    Hello h;
    string name = "zhang san";
    auto func = boost::bind(&Hello::say, &h, std::ref(name));
    //std::function<void()> func;
    //func = std::bind(&Hello::say, h, std::ref(name));
    func();
}
