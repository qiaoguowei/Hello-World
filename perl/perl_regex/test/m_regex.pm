#!/usr/bin/perl

use Encode;

$name_candidate_reg = qr/(?<![\x{4e00}-\x{9fa5}])[\x{4e00}-\x{9fa5}]{2,4}?(?![\x{4e00}-\x{9fa5}])/;

sub hasChineseNames
{
	$text = shift;

	while ($text =~ m/($name_candidate_reg)/g)
	{
		my $name_candidate = $1;
		printf("%s\n", $1);
	}
	print("no matched\n");
}

my $text = "乔国伟少时诵诗书所，世是。收拾收拾sss";
#my $text = ",三生三世.";
Encode::_utf8_on($text);
hasChineseNames($text);
