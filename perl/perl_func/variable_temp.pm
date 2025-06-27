#!/usr/bin/perl

# 全局变量
# 我们可以使用 local 为全局变量提供临时的值，在退出作用域后将原来的值还回去。
$string = "Hello, World!";

sub PrintRunoob
{
	# PrintHello 函数私有变量
	local $string;
	$string = "Hello, Runoob!";
	# 子程序调用的子程序
	PrintMe();
	print "PrintRunoob 函数内字符串值：$string\n";
}
sub PrintMe
{
	print "PrintMe 函数内字符串值：$string\n";
}

sub PrintHello
{
	print "PrintHello 函数内字符串值：$string\n";
}

# 函数调用
PrintRunoob();
PrintHello();
print "函数外部字符串值：$string\n";
