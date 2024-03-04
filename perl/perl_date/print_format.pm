#!/usr/bin/perl

($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime();
 
printf("格式化时间：HH:MM:SS\n");
printf("%02d:%02d:%02d\n", $hour, $min, $sec);
