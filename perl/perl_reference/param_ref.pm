#!/usr/bin/perl

sub myprint
{
	my $scalar1 = shift;
	my $array2 = shift;
	my $hash3 = shift;

	print "$scalar1\n";
	print "@$array2\n";

	foreach my $mykey (keys %$hash3)
	{
		my $value = %$hash3{$mykey};
		print "$mykey -> $value\n";
	}
}

$var = "aaaaa";
@var2 = ("aaa", "bbb", "ccc");
%var3 = ("1" => "aaa", "2" => "bbb", "3" => "ccc");

myprint($var, \@var2, \%var3);
