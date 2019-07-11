CC=g++

all: main.o
	$(CC) -o kaiketsu main.o

main.o: main.cpp
	$(CC) -c main.cpp

.PHONY: clean

clean:
	rm -f kaiketsu main.o