#!/usr/bin/python3

path_str =r'C:\\Users\\Administrator\\data\\denoising\\test_color\\15.jpg'
print(path_str)
path_str = path_str.replace('\\', '\\\\')
print(path_str)
path_str = path_str.replace('\\\\', '\\')
print(path_str)

xxx_str = r"td3_rf\\admin"
if ('\\\\' in xxx_str):
    print(xxx_str)
