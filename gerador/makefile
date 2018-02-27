CC=g++
OU=-std=c++11

generator: generator.cpp Vertex.o create.o
	$(CC) $(OU) generator.cpp -o generator Vertex.o create.o

create.o: create.cpp 
	$(CC) $(OU) create.cpp -c

Vertex.o: Vertex.cpp 
	$(CC) $(OU) Vertex.cpp -c

final: generator cleanObj

clean: cleanObj cleanFiles


cleanObj:
	rm -f *.o

cleanFiles:
	rm -f *.3d
