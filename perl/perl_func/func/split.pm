#!/usr/bin/perl

use Encode;

sub is_valid_HKID
{
	my $matched = shift;
	my @input = split '', lc($matched); #lc将大写转为小写
	if (@input == 10)
	{
		print "there are ten characters in the string.\n";
		print "@input\n";
	}
}

my $mymatched = "AAAAAAAAAA";
#is_valid_HKID($mymatched);

sub test_split
{
	my $matched = shift;
	my @input = split(/\s/m, $matched);

	foreach(@input)
	{
		print length($_);
		print("    $_\n");
	}
}

my $test_txt = "你是，我是， 他是	是哦aa始发地，来了";
Encode::_utf8_on($test_txt);
test_split($test_txt);
