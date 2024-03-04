#!/usr/bin/python3

test_str = 'destinations.ipAddress.raw'
test_list = test_str.split('.')

print(test_list)

if test_list[-1] == 'raw':
    del test_list[-1]

print(test_list)
