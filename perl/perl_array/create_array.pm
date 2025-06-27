#!/usr/bin/perl

#数组变量以 @ 符号开始，元素放在括号内，也可以以 qw 开始定义数组。
@array = (1, 2, 'Hello');
@array1 = qw/这是 一个 数组/;
@days = qw/google
taobao
...
runoob/;

print "@array\n";
print "@array1\n";
print "@days\n";
