#!/usr/bin/perl

$a = 20;
# 使用 unless 语句检测布尔表达式
unless( $a  ==  30 )
{
	# 布尔表达式为 false 时执行
	printf "a 的值不为 30\n";
}
elsif( $a ==  30 )
{
	# 布尔表达式为 true 时执行
	printf "a 的值为 30\n";
}
else
{
	# 没有条件匹配时执行
	printf "a  的 值为 $a\n";
}
