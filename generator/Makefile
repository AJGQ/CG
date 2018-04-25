CC=g++ -g
OU=-std=c++11
PROJECT_NAME=generator

generator: main.cpp create.o bezierPatch.o
	$(CC) $(OU) main.cpp create.o bezierPatch.o -o $(PROJECT_NAME)

create.o: create.cpp
	$(CC) $(OU) create.cpp -c

bezierPatch.o: bezierPatch.cpp
	$(CC) $(OU) bezierPatch.cpp -c


clean:
	rm -f *.o

