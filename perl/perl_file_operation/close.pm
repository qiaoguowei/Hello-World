#!/usr/bin/perl

#close FILEHANDLE
#close
#FILEHANDLE 为指定的文件句柄，如果成功关闭则返回 true。

sysopen(DATA, "file.txt", O_RDWR);
close(DATA) || die "无法关闭文件";
