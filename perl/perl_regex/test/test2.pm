#!/usr/bin/perl

use Encode;
my $reg_city_prefix = qr/(\x{5317}\x{4eac}\x{5e02}?)/;

my $text = "北京";
Encode::_utf8_on($text);
if ($text =~ /($reg_city_prefix)/ug)
{
	print "$&\n";
}
else
{
	print "no matched.\n";
}
