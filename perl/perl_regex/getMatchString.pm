#!/usr/bin/perl

sub has_valid_regexp
{
	my $text = shift;
	my $reg = shift;
	my @final_return_info;

	if ($text =~ /$reg/ixg)
	{
		push @final_return_info, $&;
	}
	else
	{
		push @final_return_info, '000';
	}
	push @final_return_info, '111';

	return @final_return_info;
}

$gtext = "111777199703313333";
$greg = qr /(^\d{18}$)/;
@return_info = has_valid_regexp($gtext, $greg);
foreach (@return_info)
{
	print "$_\n";
}
