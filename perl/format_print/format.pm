#!/usr/bin/perl

#format FormatName =
#fieldline
#value_one, value_two, value_three
#fieldline
#value_one, value_two
#
#FormatName ：格式化名称。
#fieldline ：一个格式行，用来定义一个输出行的格式,类似 @,^,<,>,| 这样的字符。
#value_one,value_two…… ：数据行，用来向前面的格式行中插入值,都是perl的变量。
#. ：结束符号。

$text = "google runoob taobao";
format STDOUT =
first: ^<<<<<  # 左边对齐，字符长度为6
$text
second: ^<<<<< # 左边对齐，字符长度为6
$text
third: ^<<<< # 左边对齐，字符长度为5，taobao 最后一个 o 被截断
$text  
.
write
