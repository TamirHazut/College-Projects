CC=gcc
LDFLAGS=-pthread
OBJS=hw2_a.o hw2_b.o stack.o general.o
EXEC=v1 v2
CFLAGS = -std=c99

all: $(EXEC)

v1: hw2_a.o general.o
	$(CC) -o $@ $(LDFLAGS) $^

v2: hw2_b.o general.o stack.o
	$(CC) -o $@ $(LDFLAGS) $^

hw2_a.c: hw2_a.h
hw2_b.c: hw2_b.h
stack.c: stack.h
general.c: general.h

clean: 
	rm -f $(EXEC) $(OBJS)
	

