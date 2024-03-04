#!/usr/bin/perl

$a = 100;
# 使用 == 判断两个数是否相等
if( $a  ==  20 )
{
	# 条件为 true 时执行
	printf "a 的值为 20\n";
}
elsif( $a ==  30 )
{
	# 条件为 true 时执行
	printf "a 的值为 30\n";
}
else
{
	# 以上所有的条件为 false 时执行
	printf "a 的值为 $a\n";
}
