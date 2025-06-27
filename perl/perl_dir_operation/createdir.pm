#!/usr/bin/perl

$dir = "/tmp/perl";

# 在 /tmp 目录下创建 perl 目录
mkdir( $dir ) or die "无法创建 $dir 目录, $!";
print "目录创建成功\n";
