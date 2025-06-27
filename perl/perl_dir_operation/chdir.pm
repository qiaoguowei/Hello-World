#!/usr/bin/perl

$dir = "/home";

# 将当前目录移动到 /home 目录下
chdir( $dir ) or die "无法切换目录到 $dir , $!";
print "你现在所在的目录为 $dir\n";
