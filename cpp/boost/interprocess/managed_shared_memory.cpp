#include <boost/interprocess/managed_shared_memory.hpp> 
#include <iostream> 


/*
 * boost::interprocess::managed_shared_memory对于需要分配到共享内存上的对象，它能够以内存申请的方式初始化，
 *     并使其自动为使用同一个共享内存的其他应用程序可用。
 *
 * 上面的例子打开名为 "Highscore" 大小为1,024 字节的共享内存，如果它不存在，它会被自动地创建
 * 在常规的共享内存中，为了读写数据，单个字节被直接访问，托管共享内存使用诸如 construct() 函数，
 *     此函数要求一个数据类型作为模板参数，此例中声明的是 int 类型，函数缺省要求一个名称来表示在共享
 *     内存中创建的对象。 此例中使用的名称是 "Integer"。
 *
 * */

void test1() 
{ 
    boost::interprocess::shared_memory_object::remove("Highscore"); 
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
    int *i = managed_shm.construct<int>("Integer")(99); 
    std::cout << *i << std::endl; 
    std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
    if (p.first) 
        std::cout << p.second << std::endl; 
}

void test2()
{
    boost::interprocess::shared_memory_object::remove("Highscore"); 
    boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024); 
    int *i = managed_shm.find_or_construct<int>("Integer")(99); 
    std::cout << *i << std::endl; 

    managed_shm.destroy<int>("Integer"); 
    std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer"); 
    std::cout << p.first << std::endl; 
}

int main()
{
    test1();
    std::cout << "========================================================" << std::endl;
    test2();
}





