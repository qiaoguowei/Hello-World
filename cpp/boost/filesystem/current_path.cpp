#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
    string workpath = "/home/qgw/SDK/boost_1_73_0/stage/lib";
    boost::filesystem::path workpathP(workpath);
    boost::filesystem::current_path(workpathP);
    boost::filesystem::path newWorkpath = boost::filesystem::current_path();

    cout << workpathP.string() << endl;
    cout << newWorkpath.string() << endl;
}
