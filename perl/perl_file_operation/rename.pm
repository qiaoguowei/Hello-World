#以下实例，我们将已存在的文件 file1.txt 重命名为 file2.txt，指定的目录是在 /usr/runoob/test/ 下：

#!/usr/bin/perl

rename ("/usr/runoob/test/file1.txt", "/usr/runoob/test/file2.txt" );
#函数 renames 只接受两个参数，只对已存在的文件进行重命名。
