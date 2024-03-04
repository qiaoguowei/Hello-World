#!/usr/bin/perl

#redo 语句直接转到循环体的第一行开始重复执行本次循环，redo语句之后的语句不再执行，continue语句块也不再执行。
#redo [LABEL]

$a = 0;
while($a < 10)
{
	if( $a == 5 )
	{
		$a = $a + 1;
		redo;
	}
	print "a = $a\n";
}
continue
{
	$a = $a + 1;
}
