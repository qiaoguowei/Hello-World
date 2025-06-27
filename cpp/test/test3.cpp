#include <iostream>
#include <fstream>

int main()
{
    std::ofstream fout("./xxx.bat");
    fout << "chcp 65001" << std::endl;
    fout << "@echo off" << std::endl;
    fout << std::endl;
    fout << ":2" << std::endl;
    fout << "choice /t 3 /d y /n >null" << std::endl;
    fout << std::endl;
    fout << "del C:\\Users\\kingdom\\Documents\\nqhq.dbf" << std::endl;
    char a = 27;
    fout << "echo " << a << "[32m删除完成" << a << "[0m" << std::endl;
    fout << "copy D:\\nqhq.dbf C:\\Users\\kingdom\\Documents\\ >null" << std::endl;
    fout << "echo 复制完成" << std::endl;
    fout << "if \"\%time\%\" GTR \"18:59:00\" (exit)" << std::endl;
    fout << "goto 2" << std::endl;

    fout.close();
}
