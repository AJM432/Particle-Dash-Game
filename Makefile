# Must add each class file in makefile as .cpp and .o
# wd = Working directory
wd = $(shell pwd)

all: main

main: main.o Particle.o
	g++ -o main main.o Particle.o -L "$(wd)/lib" -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o -I "$(wd)/include"

Particle.o: src/Particle.cpp
	g++ -c src/Particle.cpp -o Particle.o -I "$(wd)/include"

clean:
	rm -f *.o main

