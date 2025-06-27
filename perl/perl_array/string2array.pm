#!/usr/bin/perl

#split [ PATTERN [ , EXPR [ , LIMIT ] ] ]
#PATTERN：分隔符，默认为空格。
#EXPR：指定字符串数。
#LIMIT：如果指定该参数，则返回该数组的元素个数。

$var_test = "runoob";
$var_string = "www-runoob-com";
$var_names = "google,taobao,runoob,weibo";
 
#字符串转为数组
@test = split('', $var_test);
@string = split('-', $var_string);
@names  = split(',', $var_names);
 
print "$test[3]\n";  # 输出 o
print "$string[2]\n";  # 输出 com
print "$names[3]\n";   # 输出 weibo
