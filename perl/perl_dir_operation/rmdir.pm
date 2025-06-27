#!/usr/bin/perl

$dir = "/tmp/perl";

# 删除 /tmp 目录下的 perl 目录
rmdir( $dir ) or die "无法删除 $dir 目录, $!";
print "目录删除成功\n";
