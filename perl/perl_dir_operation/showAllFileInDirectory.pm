#!/usr/bin/perl

# 显示 /tmp 目录下的所有文件
$dir = "/tmp/*";
my @files = glob( $dir );

foreach (@files )
{
	print $_ . "\n";
}

# 显示 /tmp 目录下所有以 .c 结尾的文件
$dir = "/tmp/*.c";
@files = glob( $dir );

foreach (@files )
{
	print $_ . "\n";
}

# 显示所有隐藏文件
$dir = "/tmp/.*";
@files = glob( $dir );
foreach (@files )
{
	print $_ . "\n";
}

# 显示 /tmp 和 /home 目录下的所有文件
$dir = "/tmp/* /home/*";
@files = glob( $dir );

foreach (@files )
{
	print $_ . "\n";
}
