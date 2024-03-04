#!/usr/bin/perl

#goto LABEL
#找出标记为 LABEL 的语句并且从那里重新执行。

$a = 10;
LOOP:do
{
	if( $a == 15)
	{
		# 跳过迭代
		$a = $a + 1;
		# 使用 goto LABEL 形式
		print "跳出输出 \n";
		goto LOOP;
		print "这一句不会被执行 \n";
	}
	print "a = $a\n";
	$a = $a + 1;
}while( $a < 20 );
