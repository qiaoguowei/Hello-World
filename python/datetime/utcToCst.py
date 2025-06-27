#!/usr/bin/python3

from datetime import datetime,timedelta

utc_time = '2023-09-20T06:19:57.898+0000'
utc_time_substr = utc_time[0:19]
print(utc_time_substr)

cst_time = datetime.strptime(utc_time_substr, "%Y-%m-%dT%H:%M:%S")+timedelta(hours=8)
print(cst_time)
cst_time_str = str(cst_time)
print(type(cst_time_str))
print(cst_time_str)
