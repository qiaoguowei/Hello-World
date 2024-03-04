#!/usr/bin/perl

# 全局变量
$string = "Hello, World!";

# 函数定义
sub PrintHello
{
	# PrintHello 函数的私有变量
	my $string;
	$string = "Hello, Runoob!";
	print "函数内字符串：$string\n";
}
# 调用函数
PrintHello();
print "函数外字符串：$string\n";
