main:	main.cpp archivo.o
	g++ main.cpp archivo.o -o main -Wall
archivo.o:	archivo.h archivo.cpp
	g++ -c archivo.cpp -Wall
clean:
	rm -f main *.o *~
