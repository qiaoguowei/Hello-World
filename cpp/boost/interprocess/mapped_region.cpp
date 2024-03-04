#include <iostream>
#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace std;

/*
 * 为了调整共享内存的大小，truncate() 函数可以被重复调用。
 * 由于共享内存被用于应用程序之间交换数据，所以每个应用程序需要映射共享内存到自己的地址空间上，这
 *     是通过 boost::interprocess::mapped_region 类实现的。
 *
 * boost::interprocess::mapped_region 还能映射不同的对象到具体应用的地址空间。 
 * boost::interprocess::file_mapping类实际上代表特定文件的共享内存。 所以 boost::interprocess::file_mapping 类型的对象对应一个文件。
 * 向这个对象写入的数据将自动保存关联的物理文件上。
 *
 * 
 *
 * */


int main()
{
    boost::interprocess::shared_memory_object::remove("Highscore");
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, 
            "Highscore", 
            boost::interprocess::read_write);

    shdmem.truncate(1024);

    boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write); 
    std::cout << std::hex << "0x" << region.get_address() << std::endl; 
    std::cout << std::dec << region.get_size() << std::endl; 
    std::cout << boost::interprocess::mapped_region::get_page_size() << endl;
    int *i1 = static_cast<int *>(region.get_address());
    *i1 = 99;

    boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only); 
    std::cout << std::hex << "0x" << region2.get_address() << std::endl; 
    std::cout << std::dec << region2.get_size() << std::endl; 
    int *i2 = static_cast<int *>(region2.get_address());
    cout << *i2 << endl;

}








