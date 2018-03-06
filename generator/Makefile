CC=g++
OU=-std=c++11
PROJECT_NAME=generator

generator: main.cpp create.o
	$(CC) $(OU) main.cpp create.o -o $(PROJECT_NAME)

create.o: create.cpp 
	$(CC) $(OU) create.cpp -c

final: generator cleanObj

clean: cleanObj cleanFiles


cleanObj:
	rm -f *.o

cleanFiles:
	rm -f *.3d
