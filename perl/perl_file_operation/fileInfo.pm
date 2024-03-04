#/usr/bin/perl

my $file = "/home/qgw/my_github/Hello-World/perl/perl_file_operation/file2.txt";
my (@description, $size);
if (-e $file)
{
	push @description, '是一个二进制文件' if (-B _);
	push @description, '是一个socket(套接字)' if (-S _);
	push @description, '是一个文本文件' if (-T _);
	push @description, '是一个特殊块文件' if (-b _);
	push @description, '是一个特殊字符文件' if (-c _);
	push @description, '是一个目录' if (-d _);
	push @description, '文件存在' if (-x _);
	push @description, (($size = -s _)) ? "$size 字节" : '空';
	print "$file 信息：", join(', ',@description),"\n";
}

#-A	文件上一次被访问的时间(单位：天)
#-B	是否为二进制文件
#-C	文件的(inode)索引节点修改时间(单位：天)
#-M	文件上一次被修改的时间(单位：天)
#-O	文件被真实的UID所有
#-R	文件或目录可以被真实的UID/GID读取
#-S	为socket(套接字)
#-T	是否为文本文件
#-W	文件或目录可以被真实的UID/GID写入
#-X	文件或目录可以被真实的UID/GID执行
#-b	为block-special (特殊块)文件(如挂载磁盘)
#-c	为character-special (特殊字符)文件(如I/O 设备)
#-d	为目录
#-e	文件或目录名存在
#-f	为普通文件
#-g	文件或目录具有setgid属性
#-k	文件或目录设置了sticky位
#-l	为符号链接
#-o	文件被有效UID所有
#-p	文件是命名管道(FIFO)
#-r	文件可以被有效的UID/GID读取
#-s	文件或目录存在且不为0(返回字节数)
#-t	文件句柄为TTY(系统函数isatty()的返回结果；不能对文件名使用这个测试)
#-u	文件或目录具有setuid属性
#-w	文件可以被有效的UID/GID写入
#-x	文件可以被有效的UID/GID执行
#-z	文件存在，大小为0(目录恒为false)，即是否为空文件，
