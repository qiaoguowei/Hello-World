#!/usr/bin/perl

# 定义函数
sub PrintList
{
	my @list = @_;
	print "列表为 : @list\n";
}
$a = 10;
@b = (1, 2, 3, 4);

# 列表参数
# 但如果我们需要传入标量和数组参数时，需要把列表放在最后一个参数上
PrintList($a, @b);
