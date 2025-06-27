#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "argv[1] = the file which copy from;" << endl;
        cout << "argv[2] = the file which copy to." << endl;
        return 0;
    }

    string fromFilename = argv[1];
    string toFilename = argv[2];

    boost::filesystem::copy_file(fromFilename, toFilename);
    return 0;
}
