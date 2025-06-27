#print 函数
#对于所有从文件句柄中读取信息的函数，在后端主要的写入函数为 print：
#
#print FILEHANDLE LIST
#print LIST
#print
#利用文件句柄和 print 函数可以把程序运行的结果发给输出设备(STDOUT：标准输出)，例如：
#
#print "Hello World!\n";

#!/usr/bin/perl

# 只读方式打开文件
open(DATA1, "<file.txt");

# 打开新文件并写入
open(DATA2, ">file2.txt");

# 拷贝数据
while(<DATA1>)
{
	print DATA2 $_;
}
close( DATA1 );
close( DATA2 );
