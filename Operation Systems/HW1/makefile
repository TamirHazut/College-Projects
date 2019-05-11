CC=gcc
OBJS=v1.o v2.o checksudokuboard.o general.o
EXEC=v1 v2 CheckSudokuBoard
CFLAGS = -std=c99

all: $(EXEC)

v1: v1.o general.o
	$(CC) -o $@ $^

v2: v2.o general.o
	$(CC) -o $@ $^

CheckSudokuBoard: checksudokuboard.o general.o
	$(CC) -o $@ $^

v1.c: v1.h
v2.c: v2.h
checksudokucols.c: checksudokucols.h
general.c: general.h

clean: 
	rm -f $(EXEC) $(OBJS)
	

