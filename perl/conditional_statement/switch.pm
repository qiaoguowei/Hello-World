#!/usr/bin/perl

use Switch;

#当匹配 case 后，会执行 case 语句块代码，执行后跳出 switch 语句。
#当匹配 case 后，如果我们需要继续执行接下来的 case 语句，则需要添加 next 语句。

$var = 10;
@array = (10, 20, 30);
%hash = ('key1' => 10, 'key2' => 20);
 
switch($var){
	case 10           { print "数字 10\n"; next; }
	case "a"          { print "字符串 a\n" }
	case [1..10,42]   { print "数字在列表中\n"; next; }
	case (\@array)    { print "数字在数组中\n"; next; }
	case (\%hash)     { print "在哈希中\n" }
	else              { print "没有匹配的条件\n" }
}
