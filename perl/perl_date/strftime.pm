#%a	星期几的简称（ Sun..Sat） *	Thu
#%A	星期几的全称（ Sunday..Saturday） *	Thursday
#%b	月的简称（Jan..Dec） *	Aug
#%B	月的全称（January..December） *	August
#%c	日期和时间 *	Thu Aug 23 14:55:02 2001
#%C	年份除于100，并取整 (00-99)	20
#%d	一个月的第几天 (01-31)	23
#%D	日期, MM/DD/YY 相等于%m/%d/%y	08/23/01
#%e	一个月的第几天，使用空格填充个位数 ( 1-31)	23
#%F	YYYY-MM-DD 的简写类似于 %Y-%m-%d	2001-08-23
#%g	年份的最后两位数 (00-99)	01
#%g	年	2001
#%h	月的简称 * (和%b选项相同)	Aug
#%H	24 小时制 (00-23)	14
#%I	12 小时制 (01-12)	02
#%j	一年的第几天 (001-366)	235
#%m	月 (01-12)	08
#%M	分钟 (00-59)	55
#%n	新行 ('\n')	
#%p	显示出AM或PM	PM
#%r	时间（hh：mm：ss AM或PM），12小时 *	02:55:02 pm
#%R	24 小时 HH:MM 时间格式,相等于 %H:%M	14:55
#%S	秒数 (00-61)	02
#%t	水平制表符 ('\t')	
#%T	时间（24小时制）（hh:mm:ss），相等于%H:%M:%S	14:55
#%u	ISO 8601 的星期几格式，星期一为1 (1-7)	4
#%U	一年中的第几周，星期天为第一天(00-53)	33
#%V	ISO 8601 第几周 (00-53)	34
#%w	一个星期的第几天（0代表星期天） (0-6)	4
#%W	一年的第几个星期，星期一为第一天 (00-53)	34
#%x	显示日期的格式（mm/dd/yy） *	08/23/01
#%X	显示时间格式 *	14:55:02
#%y	年，两位数 (00-99)	01
#%Y	年	2001
#%z	ISO 8601与UTC的时区偏移(1 minute=1, 1 hour=100)
#+100
#%Z	当前时区的名称,如"中国标准时间" *
#CDT
#%%	% 符号	%

#!/usr/bin/perl

use POSIX qw(strftime);
 
$datestring = strftime "%Y-%m-%d %H:%M:%S", localtime;
printf("时间日期 - $datestring\n");
 
#  GMT 格式化时间日期
$datestring = strftime "%Y-%m-%d %H:%M:%S", gmtime;
printf("时间日期 - $datestring\n");



