#!/usr/bin/perl

my @array111 = qw/24 374/;
my $scalar222 = 23;
if ($scalar222 ~~ @array111)
<<<<<<< HEAD
#if (grep {$scalar222 eq $_} @array111)
{
    print '$scalar222 in @array111';
    print "\n";
}
else
{
    print '$scalar222 is not in @array111';
    print "\n";
=======
{
	print '$scalar222 in @array111';
	print "\n";
>>>>>>> 4adb3f20a968faa466b0157e6da162535c178879
}
