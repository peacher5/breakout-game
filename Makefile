CC = gcc
CXX = g++

LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL

all: Breakout

cp_functions.o: cp_functions.c
	$(CC) -c cp_functions.c

mouse.o: mouse.cpp
	$(CXX) -c mouse.cpp

object.o: object.cpp
	$(CXX) -c object.cpp

ball.o: ball.cpp
	$(CXX) -c ball.cpp

brick.o: brick.cpp
	$(CXX) -c brick.cpp

in_game.o: in_game.cpp
	$(CXX) -c in_game.cpp

game_over.o: game_over.cpp
	$(CXX) -c game_over.cpp

main.o: main.cpp
	$(CXX) -c main.cpp

Breakout: main.o cp_functions.o mouse.o object.o ball.o brick.o in_game.o game_over.o
	$(CXX) -o Breakout main.o cp_functions.o mouse.o object.o ball.o brick.o in_game.o game_over.o $(LDFLAGS)

clean: 
	rm -f *.o Breakout CON

