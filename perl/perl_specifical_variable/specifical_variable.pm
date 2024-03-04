#!/usr/bin/perl

#最常用的特殊变量为 $_，该变量包含了默认输入和模式匹配内容。实例如下：
foreach ('Google','Runoob','Taobao') {
	print $_;
	print "\n";
}

#以下实例我们不使用 $_ 来输出内容：
#在迭代循环中，当前循环的字符串会放在 $_ 中。另外 print 在不指定输出变量，默认情况下使用的也是 $_。
foreach ('Google','Runoob','Taobao') {
	print;
	print "\n";
}
