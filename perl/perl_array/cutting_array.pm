#!/usr/bin/perl

@sites = qw/google taobao runoob weibo qq facebook 网易/;
 
@sites2 = @sites[3,4,5];
 
print "@sites2\n";

#如果是连续的索引，可以使用 .. 来表示指定范围：
@sites3 = @sites[3..5];
 
print "@sites3\n";
