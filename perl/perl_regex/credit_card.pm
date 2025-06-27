my %regCCN_No_Delim_hash = (
        'EU' => qr/\b(?:(?:\d{14,17})|(?:\d{18,19})|(?:(?:\d ){13,15}\d)|(?:(?:\d ){17,18}\d))\b/
        );

sub Make_Candidates_Regexp()
{
    my $ALL_DELIMITERS = qr/ \-\/\t,\?;!=<>~\+_\./;
    my $digits = '[0-9]';
    my @delimitations = (
            [6, 13],
            [6, 12],
            [6, 4, 9],
            [5, 4, 5, 5],
            [5, 5, 5, 4],
            [5, 4, 5],
            [4, 4, 4, 4, 3],
            [4, 6, 5],
            [4, 6, 4],
            [4, 4, 4, 7],
            [4, 4, 4, 3],
            [4, 4, 4, 2],
            [4, 4, 4, 4]
            );
    my $str = '\b(?:';
    for my $i (0 .. ($#delimitations - 1))
    {
        my $j_bak = 0;
        for my $j (0 .. ($#{$delimitations[$i]} -1))
        {
            $str .= sprintf("%s{%s}(?:[%s])", $digits, $delimitations[$i][$j], $ALL_DELIMITERS);
            $j_bak = $j;
        }
        $str .= sprintf("%s{%d}|", $digits, $delimitation[$i][$j_bak + 1]);
    }

    my @delimitations_lastline = @{$delimitations[$#delimitations]};
    my $x_bak=0;
    for my $x (0 .. $#delimitations_lastline -1)
    {
        $x_bak = $x;
        $str .= sprintf "%s{%d}(?:[%s])", $digits, $delimitations_lastline[$x], $ALL_DELIMITERS;
    }
    $str .= sprintf "%s{%d}", $digits, $delimitations_lastline[$x_bak + 1];
    $str .= ')\b';
    print "reg.$str\n";
    return $str;
}

sub hasCCN
{
    my $src = shift;
    return() unless $src;

    if ($src =~ /\b(?:(?:\d{14,16})|(?:\d{18,19})|(?:(?:\d ){13,15}\d)|(?:(?:\d ){17,18}\d))\b/g)
    {
        print "matched\n";
    }
    else
    {
        print "not matched\n";
    }

    $xxx = Make_Candidates_Regexp();
    #if ($src =~ $regCCN_No_Delim_hash{'EU'})
#print "$xxx\n";
    if ($src =~ /($xxx)/g)
    {
        print "============== matched in regCCN_No_Delim_hash $1\n";
        $match_end = pos $src;
        $match_start = $match_end - length($1);
        print "$match_start\n";
        print "$match_end\n";
    }
}


my $content = "4929-3813-3266-4295 5370-4638-8881-3020 4916-4811-5814-8111 4916-4034-9269-8783 5299-1561-5689-1938 5293-8502-0071-3058 5548-0246-6336-5664 4539-5385-7425-5825 4916-9766-5240-6147 4556-0072-1294-7415 4532-4220-6922-9909 4916-6734-7572-5015 5218-0144-2703-9266 5399-0706-4128-0178 5144-8691-2776-1108 5527-1247-5046-7780 4539-0031-3703-0728 5180-3807-3679-8221 5413-4428-0145-0036 4532-9929-3036-9308 5495-8602-4508-6804 5325-3256-9519-6624 4532-0065-1968-5602 3.45E+14 4716-6984-4983-6160 4539-8219-0484-7598 3.02E+13 4532-1753-6071-1112 4929381332664295";

hasCCN($content);
#Make_Candidates_Regexp();
