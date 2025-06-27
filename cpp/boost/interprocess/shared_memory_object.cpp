#include <iostream>
#include <string>
#include <unistd.h>
#include <boost/interprocess/shared_memory_object.hpp>

using namespace std;

/*
 * boost::interprocess::shared_memory_object的构造函数需要三个参数
 * 第一个参数指定共享内存是要创建或打开
 * 用 boost::interprocess::open_or_create 作为参数，共享内存如果存在就将其打开，否则创建之
 * 为了唯一标识一块共享内存，需要为其指定一个名称，构造函数的第二个参数指定了这个名称。
 * 第三个，也就是最后一个参数指示应用程序如何访问共享内存
 *
 * 在创建一个 boost::interprocess::shared_memory_object 类型的对象后，相应的共享内存就在操作系统中建立了
 * 可是此共享内存区域的大小被初始化为0.为了使用这块区域，需要调用 truncate() 函数，
 *     以字节为单位传递请求的共享内存的大小.
 * 
 * 请注意，truncate() 函数只能在共享内存以 boost::interprocess::read_write 方式打开时调用。 如果不
 *     是以此方式打开，将抛出 boost::interprocess::interprocess_exception 异常。
 *
 * 在创建共享内存后，get_name() 和 get_size() 函数可以分别用来查询共享内存的名称和大小。
 *
 *	
 *
 * */


int main()
{
    boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create,
            "Highscore",
            boost::interprocess::read_write);

    shdmem.truncate(1024);

    std::cout << shdmem.get_name() << std::endl;
    boost::interprocess::offset_t size;
    if (shdmem.get_size(size))
        std::cout << size << std::endl;
    sleep(10);
}




























