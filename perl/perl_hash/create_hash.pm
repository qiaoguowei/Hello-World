#!/usr/bin/perl

#为每个 key 设置 value
$data{'google'} = 'google.com';
$data{'runoob'} = 'runoob.com';
$data{'taobao'} = 'taobao.com';

#列表中第一个元素为 key，第二个为 value。
%data = ('google', 'google.com', 'runoob', 'runoob.com', 'taobao', 'taobao.com');

#可以使用 => 符号来设置 key/value:
%data = ('google'=>'google.com', 'runoob'=>'runoob.com', 'taobao'=>'taobao.com');

#以下实例是上面实例的变种，使用 - 来代替引号：
%data = (-google=>'google.com', -runoob=>'runoob.com', -taobao=>'taobao.com');

#使用这种方式 key 不能出现空格，读取元素方式为：
$val = $data{-google}
$val = $data{-runoob}



