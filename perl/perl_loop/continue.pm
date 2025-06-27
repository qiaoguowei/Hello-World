#!/usr/bin/perl

#continue 语句可用在 while 和 foreach 循环中。

$a = 0;
while($a < 3){
	print "a = $a\n";
}continue{
	$a = $a + 1;
}

@list = (1, 2, 3, 4, 5);
foreach $a (@list){
	print "a = $a\n";
}continue{
	last if $a == 4;
}
