CC	= gcc
CFLAGS	= -g -std=c99 -Wall -Wextra -Werror
CFLAGS	+= -Wno-unused-parameter -Wno-unused-function
OBJS	= main.o poly.o error.o

all: $(OBJS)
	$(CC) $(OBJS) -o p
	./p > out
	diff out correct

clean:
	rm -f *.o p out
