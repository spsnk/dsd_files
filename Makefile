main:	main.cpp archivo.o
	g++ main.cpp archivo.o -o main
archivo.o:	archivo.h archivo.cpp
	g++ -c archivo.cpp
clean:
	rm -f main *.o *~
