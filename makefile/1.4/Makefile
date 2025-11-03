#避免在同一个目录里面出现同名的目标
.PHONY: main clean
simple: main.o foo.o
	gcc -o simple main.o foo.o
main.o: main.c
	gcc -o main.o -c main.c
foo.o: foo.c
	gcc -o foo.o -c foo.c
clean:
	rm simple main.o foo.o
