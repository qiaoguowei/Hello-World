#!/usr/bin/perl
#
#open FILEHANDLE, EXPR
#open FILEHANDLE
#
#sysopen FILEHANDLE, FILENAME, MODE, PERMS
#sysopen FILEHANDLE, FILENAME, MODE
#
#FILEHANDLE：文件句柄，用于存放一个文件唯一标识符。
#EXPR：文件名及文件访问类型组成的表达式。
#MODE：文件访问类型。
#PERMS：访问权限位(permission bits)。

#以下代码我们使用 open 函数以只读的方式(<)打开文件 file.txt：

#< 或 r	只读方式打开，将文件指针指向文件头。
#> 或 w	写入方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
#>> 或 a	写入方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。
#+< 或 r+	读写方式打开，将文件指针指向文件头。
#+> 或 w+	读写方式打开，将文件指针指向文件头并将文件大小截为零。如果文件不存在则尝试创建之。
#+>> 或 a+	读写方式打开，将文件指针指向文件末尾。如果文件不存在则尝试创建之。

open(DATA, "<file.txt") or die "file.txt 文件无法打开, $!";

while(<DATA>)
{
	print "$_";
}
