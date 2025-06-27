#!/usr/bin/perl
#
#O_RDWR	读写方式打开，将文件指针指向文件头。
#O_RDONLY	只读方式打开，将文件指针指向文件头。
#O_WRONLY	写入方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
#O_CREAT	创建文件
#O_APPEND	追加文件
#O_TRUNC	将文件大小截为零
#O_EXCL	如果使用O_CREAT时文件存在,就返回错误信息,它可以测试文件是否存在
#O_NONBLOCK	非阻塞I/O使我们的操作要么成功，要么立即返回错误，不被阻塞。

#以下实例是以读写(+<filename)的方式打开文件：

sysopen(DATA, "file.txt", O_RDWR);

#如果需要在更新文件前清空文件，则写法如下：

sysopen(DATA, "file.txt", O_RDWR|O_TRUNC );
