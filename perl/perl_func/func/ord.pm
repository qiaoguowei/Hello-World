#!/usr/bin/perl

use Encode;
use strict;

#ord()
#ord EXPR ord()函数实例代码。返回由EXPR指定的字符的ASCII数值

sub test_ord
{
	my $str1 = shift;
	my $str1_num1 = ord(substr($str1, 0, 1));
	my $str1_num2 = ord(substr($str1, 1, 1));
	my $str1_num3 = ord(substr($str1, 2, 1));

	print(length($str1), "\n");
	print("ord(): $str1_num1\n");
	print("ord(): $str1_num2\n");
	printf("ord(): %x\n", $str1_num3);

	#my $str1_num = str1_num1 << 
}

my $str1 = "乔gw";
Encode::_utf8_on($str1);
#Encode::_utf8_off($str1);
test_ord($str1);
