#!/usr/bin/perl

open(DATA,"<file.txt") or die "无法打开数据";
@lines = <DATA>;
print @lines;    # 输出数组内容
close(DATA);
