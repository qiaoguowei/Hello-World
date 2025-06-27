#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <set>
//#include <boost/lexical_cast.hpp>

using namespace std;

bool stringCompare(string& src1, string& src2)
{
    try
    {
        size_t src1_pos1 = src1.find("_");
        size_t src1_pos2 = src1.find("_", src1_pos1+1);
        //int src1_num1 = boost::lexical_cast<int>(src1.substr(src1_pos1+1, src1_pos2 - src1_pos1));
        int src1_num1 = stoi(src1.substr(src1_pos1+1, src1_pos2 - src1_pos1 - 1));
        size_t src1_pos3 = src1.find("_", src1_pos2+1);
        //int src1_num2 = boost::lexical_cast<int>(src1.substr(src1_pos3));
        int src1_num2 = stoi(src1.substr(src1_pos3+1));

        size_t src2_pos1 = src2.find("_");
        size_t src2_pos2 = src2.find("_", src2_pos1+1);
        //int src2_num1 = boost::lexical_cast<int>(src2.substr(src2_pos1+1, src2_pos2 - src2_pos2));
        int src2_num1 = stoi(src2.substr(src2_pos1+1, src2_pos2 - src2_pos2 - 1));
        size_t src2_pos3 = src2.find("_", src2_pos2+1);
        //int src2_num2 = boost::lexical_cast<int>(src2.substr(src2_pos3));
        int src2_num2 = stoi(src2.substr(src2_pos3+1));

        if (src1_num1 > src2_num1)
            return true;
        else if (src1_num1 < src2_num1)
            return false;
        else
        {
            if (src1_num2 > src2_num2)
                return true;
            else if (src1_num2 < src2_num2)
                return false;
            else
                return true;
        }

    }
    catch (exception &e)
    {
        cout << "throw: " << e.what() << endl;
    }
    return true;
}

class MyStringGreater
{
public:
bool operator() (string& src1, string& src2)
{
    try
    {
        size_t src1_pos1 = src1.find("_");
        size_t src1_pos2 = src1.find("_", src1_pos1+1);
        //int src1_num1 = boost::lexical_cast<int>(src1.substr(src1_pos1+1, src1_pos2 - src1_pos1));
        int src1_num1 = stoi(src1.substr(src1_pos1+1, src1_pos2 - src1_pos1 - 1));
        size_t src1_pos3 = src1.find("_", src1_pos2+1);
        //int src1_num2 = boost::lexical_cast<int>(src1.substr(src1_pos3));
        int src1_num2 = stoi(src1.substr(src1_pos3+1));

        size_t src2_pos1 = src2.find("_");
        size_t src2_pos2 = src2.find("_", src2_pos1+1);
        //int src2_num1 = boost::lexical_cast<int>(src2.substr(src2_pos1+1, src2_pos2 - src2_pos2));
        int src2_num1 = stoi(src2.substr(src2_pos1+1, src2_pos2 - src2_pos2 - 1));
        size_t src2_pos3 = src2.find("_", src2_pos2+1);
        //int src2_num2 = boost::lexical_cast<int>(src2.substr(src2_pos3));
        int src2_num2 = stoi(src2.substr(src2_pos3+1));

        if (src1_num1 > src2_num1)
            return true;
        else if (src1_num1 < src2_num1)
            return false;
        else
        {
            if (src1_num2 > src2_num2)
                return true;
            else if (src1_num2 < src2_num2)
                return false;
            else
                return true;
        }

    }
    catch (exception &e)
    {
        cout << "throw: " << e.what() << endl;
    }
    return true;
}

};

int main()
{
    ifstream fin("./DirectoryString");

    if (!fin.is_open())
    {
        cout << "open file failed." << endl;
        return -1;
    }

    //std::set<std::string, MyStringGreater> DirName;
    std::vector<string> DirName;
    char buf[128];
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        fin.getline(buf, sizeof(buf)-1);
        if (fin.eof())
            break;
        //DirName.insert(string(buf));
        DirName.push_back(string(buf));
    }
    std::sort(DirName.begin(), DirName.end(), stringCompare);

    for (auto &x : DirName)
    {
        cout << x << endl;
    }
}














