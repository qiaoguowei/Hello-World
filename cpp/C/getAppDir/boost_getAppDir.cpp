#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

int main()
{
    if (boost::filesystem::exists("/proc/self/exe"))
    {
        cout << "/proc/self/exe is exists." << endl;
        string mPath = boost::filesystem::read_symlink("/proc/self/exe").string();
        cout << mPath << endl;
    }

    if (boost::filesystem::exists("/proc/curproc/file"))
    {
        cout << "/proc/curproc/file is exists." << endl;
        string mPath = boost::filesystem::read_symlink("/proc/curproc/file").string();
        cout << mPath << endl;
    }

    if (boost::filesystem::exists("/proc/curproc/exe"))
    {
        cout << "/proc/curproc/exe is exists." << endl;
        string mPath = boost::filesystem::read_symlink("/proc/curproc/file").string();
        cout << mPath << endl;
    }
}
