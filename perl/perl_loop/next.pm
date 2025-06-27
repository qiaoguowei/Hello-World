#!/usr/bin/perl

#next [ LABEL ];
#其中 LABEL 是可选的，如果没有指定 LABEL，next 语句将返回到循环体的起始处开始执行下一次循环。

$a = 10;
while( $a < 20 ){
	if( $a == 15)
	{
		# 跳出迭代
		$a = $a + 1;
		next;
	}
	print "a 的值为: $a\n";
	$a = $a + 1;
}
