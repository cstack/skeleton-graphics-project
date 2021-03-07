run: main
	./main

main: main.o simple_graphics_library.o glad.o
	g++ -o main -lglfw main.o simple_graphics_library.o glad.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

simple_graphics_library.o: simple_graphics_library.cpp simple_graphics_library.h
	g++ -c simple_graphics_library.cpp -o simple_graphics_library.o

glad.o: glad.c
	gcc -c -o glad.o glad.c

lint:
	clang-format -i *.cpp *.h

clean: 
	rm -f main *.o