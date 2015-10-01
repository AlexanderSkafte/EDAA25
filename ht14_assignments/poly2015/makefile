##
## Simple and effective makefile :)
##

CC	= gcc
CFLAGS	= -std=c99 -g -W -Wall -pedantic
OBJS 	= poly.o list.o main.o
DEPS	= poly.h
PROG	= out

default: all
 
all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

.PHONY: clean
clean:
	rm *.o
	rm $(PROG)
