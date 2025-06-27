#!/usr/bin/perl

# 函数定义
sub PrintHash
{
	my (%hash) = @_;

	foreach $item (%hash){
		print "元素 : $item\n";
	}
}
%hash = ('name' => 'runoob', 'age' => 3);

# 创建函数的引用 函数引用格式: \&
$cref = \&PrintHash;

# 使用引用调用函数 调用引用函数格式: & + 创建的引用名。
&$cref(%hash);
