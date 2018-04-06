CC = gcc
CXX = g++

LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL

all: Breakout

cp_functions.o: cp_functions.c
	$(CC) -c cp_functions.c

main.o: main.cpp
	$(CXX) -c main.cpp

Breakout: cp_functions.o main.o
	$(CXX) -o Breakout cp_functions.o main.o $(LDFLAGS)

clean: 
	rm -f *.o Breakout CON

