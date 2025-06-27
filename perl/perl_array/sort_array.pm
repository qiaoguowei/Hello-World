#!/usr/bin/perl

#sort [ SUBROUTINE ] LIST
#SUBROUTINE：指定规则。
#LIST：列表或数组。

# 定义数组
@sites = qw(google taobao runoob facebook);
print "排序前: @sites\n";
 
# 对数组进行排序
@sites = sort(@sites);
print "排序后: @sites\n";
