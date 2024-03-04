#!/usr/bin/perl

my @array111 = qw/24 374/;
my $scalar222 = 23;
if ($scalar222 ~~ @array111)
{
	print '$scalar222 in @array111';
	print "\n";
}
