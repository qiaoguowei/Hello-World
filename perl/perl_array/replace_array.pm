#!/usr/bin/perl

#splice @ARRAY, OFFSET [ , LENGTH [ , LIST ] ]
#@ARRAY：要替换的数组。
#OFFSET：起始位置。
#LENGTH：替换的元素个数。
#LIST：替换元素列表。

@nums = (1..20);
print "替换前 - @nums\n";
 
splice(@nums, 5, 5, 21..25); 
print "替换后 - @nums\n";
