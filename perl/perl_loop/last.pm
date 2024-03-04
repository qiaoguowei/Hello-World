#!/usr/bin/perl

# last 语句用于退出循环语句块，从而结束循环，last语句之后的语句不再执行，continue语句块也不再执行。
# 和break相似

$a = 10;
while( $a < 20 ){
	if( $a == 15)
	{
		#退出循环
		$a = $a + 1;
		last;
	}
	print "a 的值为: $a\n";
	$a = $a + 1;
}
