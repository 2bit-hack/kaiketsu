CC=g++

all: main.o
	$(CC) -O3 -o kaiketsu main.o

main.o: src/main.cpp
	$(CC) -O3 -c src/main.cpp

.PHONY: clean

clean:
	rm -f kaiketsu main.o
