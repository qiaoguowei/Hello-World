#!/usr/bin/python3

f = open('./test.txt', 'w+', encoding='utf-8')
#f = open('./test.txt', 'wb')
f.write('This is write method')

f.seek(0, 0)
ret = f.read()
print(ret)
f.close()
