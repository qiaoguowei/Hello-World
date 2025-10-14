CC := g++
CFLAGS := -Wall -O2
TARGET := exec
OBJS := main.o AVLTree.o

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o $(TARGET)
