#!/usr/bin/perl

sub checkID
{
    my @factor = (7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2);
    my @parity = (1, 0, 'X', 9, 8, 7, 6, 5, 4, 3, 2);
    my $sum = 0;
    my $inputStr = shift;

    foreach (0..16)
    {
        my $string = substr($inputStr, $_, 1);
        $sum = $sum + ($string * $factor[$_]);
    }
    my $remainder_number = $sum % 11;
    print($remainder_number);
    print("\n");
}

sub checkID2
{
    my @factor = (7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2);
    my @parity = (1, 0, 'X', 9, 8, 7, 6, 5, 4, 3, 2);
    my $sum = 0;

    foreach(0..16)
    {
        my $string = substr($_[0], $_, 1);
        $sum = $sum + ($string * $factor[$_]);
    }
    my $remainder_number = $sum % 11;
    if ((@parity[$remainder_number]) == (substr($_[0], 17, 1)))
    {
        print "1";
    }
    print("\n");
}

$this_str = "110101200803076054";
checkID2($this_str);




