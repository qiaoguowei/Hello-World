#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main() {
    // 示例 1：绝对路径规范化
    fs::path p1 = "/a/./b/../c//d";
    fs::path normalized_p1 = p1.normalize();
    std::cout << "Normalized p1: " << normalized_p1.string() << std::endl;  // 输出: /a/c/d

    // 示例 2：相对路径规范化
    fs::path p2 = "src/../include/./header";
    fs::path normalized_p2 = p2.normalize();
    std::cout << "Normalized p2: " << normalized_p2 << std::endl;  // 输出: include/header

    // 示例 3：包含无效父目录（会抛出异常）
    try {
        fs::path p3 = "/root/../../invalid";
        std::cout << p3.normalize() << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;  // 输出错误信息
    }

    return 0;
}

