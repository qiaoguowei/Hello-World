#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;

/*
 * path complete(const path& p) { return absolute(p, initial_path()); } // = current_path() //getcwd()
 * path complete(const path& p, const path& base) { return absolute(p, base); }
 *
 * path absolute(const path& p, const path& base=current_path());
 * */

int main()
{
    boost::filesystem::path mPath("test_resize_file.txt");

    if (mPath.is_relative())
    {
        mPath = boost::filesystem::complete(mPath);
    }

    cout << mPath.string() << endl;
}
