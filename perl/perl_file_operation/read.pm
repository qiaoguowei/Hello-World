#read 函数
#read 函数用于从缓冲区的文件句柄读取信息。
#
#这个函数用于从文件读取二进制数据。
#
#read FILEHANDLE, SCALAR, LENGTH, OFFSET
#read FILEHANDLE, SCALAR, LENGTH
#参数说明:
#
#FILEHANDLE：文件句柄，用于存放一个文件唯一标识符。
#SCALAR：存贮结果，如果没有指定OFFSET，数据将放在SCALAR的开头。否则数据放在SCALAR中的OFFSET字节之后。
#LENGTH：读取的内容长度。
#OFFSET：偏移量。
#
#如果读取成功返回读取的字节数，如果在文件结尾返回 0，如果发生错误返回 undef。
