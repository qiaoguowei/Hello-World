#避免在同一个目录里面出现同名的目标
.PHONY: clean
CC = gcc
RM = rm
EXE = simple
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -c

all: first second third
	@echo "\$$@ = $@"#目标名
	@echo "$$^ = $^"#所有的依赖
	@echo "$$< = $<"#第一个依赖
first:
	@echo "1 first"
second:
	@echo "2 second"
third:
	@echo "3 third"

#wildcard 通配符函数
SRCS=$(wildcard *.c)
#patsubst 字符串替换   $(patsubst pattern,replacement,text)
OBJS=$(patsubst %.c, %.o, $(SRCS))

