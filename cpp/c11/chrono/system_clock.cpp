#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;
/*
template< class CharT >
put_time( const std::tm* tmb, const CharT* fmt );

tmb     -   指向从 localtime() 或 gmtime() 获得的日历时间结构体的指针
fmt     -   指向指定转换格式的空终止 CharT 串的指针。
    F : 等价于"%Y-%m-%d"（ ISO 8601 日期格式）。
    T : 等价于"%H:%M:%S"（ ISO 8601 时间格式）。
 */

std::string asString(const std::chrono::system_clock::time_point& tp)
{
    // to_time_t()：将时间点转换为 C 风格的 time_t
    // from_time_t()：从 time_t 转换回时间点
    time_t t = std::chrono::system_clock::to_time_t(tp);
    std::cout << "asString() : " << std::put_time(std::localtime(&t), "%F %T") << std::endl;
    std::string ts = ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

int main()
{
    std::chrono::system_clock::time_point tp;
    std::cout << "epoch: " << asString(tp) << endl;

    // now()：获取当前时间点
    tp = std::chrono::system_clock::now();
    cout << "now: " << asString(tp) << endl;

    tp = std::chrono::system_clock::time_point::min();
    cout << "min: " << asString(tp) << endl;

    tp = std::chrono::system_clock::time_point::max();
    cout << "max: " << asString(tp) << endl;
}











