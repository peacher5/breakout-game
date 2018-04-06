CC = gcc
CXX = g++

LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL

all: Breakout

cp_functions.o: cp_functions.c
	$(CC) -c cp_functions.c

object.o: object.cpp
	$(CXX) -c object.cpp

ball.o: ball.cpp
	$(CXX) -c ball.cpp

brick.o: brick.cpp
	$(CXX) -c brick.cpp

main.o: main.cpp
	$(CXX) -c main.cpp

Breakout: cp_functions.o main.o object.o ball.o brick.o
	$(CXX) -o Breakout main.o cp_functions.o object.o ball.o brick.o $(LDFLAGS)

clean: 
	rm -f *.o Breakout CON

