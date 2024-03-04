#!/usr/bin/perl

use feature 'state';

# state操作符功能类似于C里面的static修饰符，state关键字将局部变量变得持久。
sub PrintCount
{
	state $count = 0; # 初始化变量

	print "counter 值为：$count\n";
	$count++;
}

for (1..5)
{
	PrintCount();
}
