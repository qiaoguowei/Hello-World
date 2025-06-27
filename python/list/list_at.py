#!/usr/bin/python3

my_str = 'source.logonName'
my_list = my_str.split('.')

print(my_list[0])
print(my_list[1])
if type(my_list) == list:
    print('my_list is a list')

str2 = 'destination'
list2 = str2.split('.')

print(list2)
