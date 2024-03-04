#!/usr/bin/perl

@hits = (25, 30, 40);             
@names = ("google", "runoob", "taobao");

#访问数组元素使用 $ + 变量名称 + [索引值] 格式来读取，实例如下：
 
print "\$hits[0] = $hits[0]\n";
print "\$hits[1] = $hits[1]\n";
print "\$hits[2] = $hits[2]\n";
print "\$names[0] = $names[0]\n";
print "\$names[1] = $names[1]\n";
print "\$names[2] = $names[2]\n";


#数组序列号   可以按序列输出的数组形式，格式为 起始值 + .. + 结束值，实例如下：
@var_10 = (1..10);
@var_20 = (10..20);
@var_abc = ('a'..'z');
 
print "@var_10\n";   # 输出 1 到 10
print "@var_20\n";   # 输出 10 到 20
print "@var_abc\n";  # 输出 a 到 z

#数组大小  由数组中的标量上下文决定：
@array1 = (1,2,3);
print "数组大小: ",scalar @array1,"\n";

@array = (1,2,3);
$array[50] = 4;
 
$size = @array;
$max_index = $#array;
 
print "数组大小:  $size\n";
print "最大索引: $max_index\n";






