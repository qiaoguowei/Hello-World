#!/usr/bin/perl

opendir (DIR, '.') or die "无法打开目录, $!";
while ($file = readdir DIR) 
{
	print "$file\n";
}
closedir DIR;

opendir(DIR, '.') or die "无法打开目录, $!";
foreach (sort grep(/^.*\.pm$/,readdir(DIR)))
{
	print "$_\n";
}
closedir DIR;
