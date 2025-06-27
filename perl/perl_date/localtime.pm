#!/usr/bin/perl

@month = qw(一月 二月 三月 四月 五月 六月 七月 八月 九月 十月 十一月 十二月);
@day = qw(星期天 星期一 星期二 星期三 星期四 星期五 星期六);

($sec, $min, $hour, $mday, $mon, $year, $wday, $yday, $isdst) = localtime();
print "$mday $month[$mon], $day[$wday]\n";

$datestring = localtime();
print "时间日期: $datestring\n";
