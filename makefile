CC=gcc
CFLAGS=-std=c17
LDFLAGS=-lm -lSDL2
PROJECT_NAME=gameOfLife

build: main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROJECT_NAME) main.c

clean:
	rm -f $(PROJECT_NAME)
