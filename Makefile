all: make

make: aes.o 
	g++ aes.o -o make

aes.o: aes.cpp
	g++ -std=c++0x aes.cpp

clean:
	rm -rf *o make
