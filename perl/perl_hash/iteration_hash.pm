#!/usr/bin/perl

%data = ('google'=>'google.com', 'runoob'=>'runoob.com', 'taobao'=>'taobao.com');
foreach $key (keys %data)
{
	print "$data{$key}\n";
}

while(($key, $value) = each(%data))
{
	print "$data{$key}\n";
}
