CC = gcc
CXX = g++

LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL
OBJECTS = cp_functions.o main.o mouse.o object.o ball.o brick.o in_game.o game_over.o scoreboard.o missile.o

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

item_brick.o: item_brick.cpp
	$(CXX) -c item_brick.cpp

in_game.o: in_game.cpp
	$(CXX) -c in_game.cpp

game_over.o: game_over.cpp
	$(CXX) -c game_over.cpp

scoreboard.o: scoreboard.cpp
	$(CXX) -c scoreboard.cpp

missile.o: missile.cpp
	$(CXX) -c missile.cpp

main.o: main.cpp
	$(CXX) -c main.cpp

Breakout: $(OBJECTS)
	$(CXX) -o Breakout $(OBJECTS) $(LDFLAGS)

clean: 
	rm -f $(OBJECTS) Breakout CON

