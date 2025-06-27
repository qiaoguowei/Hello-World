#!/usr/bin/perl

#   ?:

my $test_regex = qr/(aaa)(?:bbb)/;
#my $test_regex = "aaab";

my $text = "aaaaaabbb";

#$text =~ /$test_regex/g;
#print "$&\n";
if ($text =~ /$test_regex/ug)
{
	print "$1\n";
	printf("%d\n", length($1));
}
else
{
	print "no matched.\n";
}
