# Makefile for project "console_app"

CC		= gcc
CFLAGS	= -I.

all: app

rebuild: clean all

clean:
	rm -f *.o app

app: main.c set_opt.o
	$(CC) main.c set_opt.o $(CFLAGS) -o app

set_opt.o: set_opt.c
	$(CC) -c set_opt.c $(CFLAGS)
