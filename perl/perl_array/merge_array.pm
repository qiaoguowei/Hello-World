#!/usr/bin/perl

@numbers = (1,3,(4,5,6));
 
print "numbers = @numbers\n";

@odd = (1,3,5);
@even = (2, 4, 6);
 
@numbers = (@odd, @even);
@numbers = sort(@numbers);
 
print "numbers = @numbers\n";
