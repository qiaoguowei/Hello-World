#!/usr/bin/perl

# 方法定义
# 如果没有使用 return 语句，则子程序的最后一行语句将作为返回值。
sub add_a_b
{
	# 不使用 return
	$_[0]+$_[1];  

	# 使用 return
	# return $_[0]+$_[1];  
}
print add_a_b(1, 2);
print "\n";
