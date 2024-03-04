#!/usr/bin/python3

key_str = "OU=zj\,DC=testad,DC=com"
my_list = key_str.split(',')
print(my_list)
tmp_str = ""
tmp_list = []
for m_str in my_list:
    tmp_str = tmp_str + m_str
    if tmp_str[-1] != '\\':
        tmp_list.append(tmp_str)
        tmp_str = ""
    else:
        tmp_str = tmp_str + ','

my_list = tmp_list

print(my_list)
