#!/usr/bin/perl

$bar = "I am runoob site. welcome to runoob site.";
if ($bar =~ /run/)
{
	print "第一次匹配\n";
}
else
{
	print "第一次不匹配\n";
}

$bar = "run";
if ($bar =~ /run/)
{
	print "第二次匹配\n";
}
else
{
	print "第二次不匹配\n";
}

$string = "welcome to runoob site.";
$string =~ m/run/;
print "匹配前的字符串: $`\n";
print "匹配的字符串: $&\n";
print "匹配后的字符串: $'\n";
