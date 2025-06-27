#!/usr/bin/python3

'''
with open('pi_digits.txt') as file_object:
    contents = file_object.read()
    print(contents.rstrip()) #要删除末尾的空行，可在print语句中使用rstrip()：
'''

filename = 'pi_digits.txt'
with open(filename) as file_object:
    for line in file_object:
        print(line.rstrip())
