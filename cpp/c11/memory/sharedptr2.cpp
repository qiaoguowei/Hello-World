#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;
/*
 * 创建临时文件
 * */
class FileDeleter
{
private:
    std::string filename;

public:
    FileDeleter(const std::string& fn)
        : filename(fn)
    {
    }

    void operator()(std::ofstream *fp)
    {
        fp->close();
        std::remove(filename.c_str());
    }
};

int main()
{
    std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"), FileDeleter("tmpfile.txt"));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "I am exit." << endl;
}















