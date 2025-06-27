#!/usr/bin/perl

#特殊变量 $[ 表示数组的第一索引值，一般都为 0 ，如果我们将 $[ 设置为 1，则数组的第一个索引值即为 1，第二个为 2，以此类推。实例如下：

# 定义数组
@sites = qw(google taobao runoob facebook);
print "网站: @sites\n";
 
# 设置数组的第一个索引为 1
$[ = 1;
 
print "\@sites[1]: $sites[1]\n";
print "\@sites[2]: $sites[2]\n";
