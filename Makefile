# Makefile for project "console_app"
# Output program name: app

CC		= gcc
CFLAGS	= -I.

all: app

rebuild: clean all

clean:
	rm -f *.o app

app: main.c work_with_param.o data.o
	$(CC) main.c work_with_param.o data.o $(CFLAGS) -o app

work_with_param.o: work_with_param.c
	$(CC) -c work_with_param.c $(CFLAGS)

data.o: data.c
	$(CC) -c data.c $(CFLAGS)
