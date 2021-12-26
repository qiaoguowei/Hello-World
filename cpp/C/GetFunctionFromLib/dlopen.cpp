#include <iostream>
#include <cstdio>
#include <string>
#include <dlfcn.h>

/*
 * void *dlopen(const char *filename, int flags);
 * int dlclose(void *handle);
 * flags :
 * RTLD_LAZY:在dlopen返回前，对于动态库中存在的未定义的变量(如外部变量extern，也可以是函数)不执行解析，
 *		就是不解析这个变量的地址。
 * RTLD_NOW：与上面不同，他需要在dlopen返回前，解析出每个未定义变量的地址，如果解析不出来，在dlopen会返回NULL，
 *		错误为：undefined symbol: xxxx.......
 * RTLD_GLOBAL:它的含义是使得库中的解析的定义变量在随后的其它的链接库中变得可以使用。
 *
 * */

typedef int (*file_size)(std::string& filename); 

int main()
{
	file_size ff = NULL;
	void *m_dl_handle = NULL;
	std::string so_path = "/home/qgw/program/cplusplus/C/GetFunctionFromLib/libboost_filesystem.so.1.71.0";
	m_dl_handle = dlopen(NULL, RTLD_LAZY);
	if(!m_dl_handle)
	{
		perror("dlopen()");
		return -1;
	}
	std::cout << "dlopen success." << std::endl;
	dlerror();
	ff = dlsym(m_dl_handle, "boost::filesystem::file_size");
	if(!ff)
	{
		perror("dlsym()");
		return -1;
	}
	
	if(m_dl_handle)
		dlclose(m_dl_handle);
	
	return 0;
}





