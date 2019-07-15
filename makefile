CC=g++

all: main.o
	$(CC) -o kaiketsu main.o

main.o: src/main.cpp
	$(CC) -c src/main.cpp

.PHONY: clean

clean:
	rm -f kaiketsu main.o
