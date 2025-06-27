#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

int main()
{
    try
    {
        // 输入字符串（ISO 8601格式，Z表示UTC时间）
        const std::string time_str = "2025-03-07T04:27:36Z";

        // 解析字符串为posix_time::ptime（UTC时间）
        boost::posix_time::ptime utc_time = boost::posix_time::time_from_string(time_str);

        // 将ptime转换为time_t（内部已处理UTC到Unix时间戳的转换）
        time_t unix_time = boost::posix_time::to_time_t(utc_time);

        std::cout << "Unix时间戳: " << unix_time << std::endl;
        return 0;
    }
    //catch (const boost::date_time::time_parsing_error& e)
    catch (const std::exception& e)
    {
        std::cerr << "时间解析错误: " << e.what() << std::endl;
        return 1;
    }
}

