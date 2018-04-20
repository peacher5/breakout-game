CC = gcc
CXX = g++

CFLAGS =
LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL

OBJECTS = cp_functions.o main.o mouse.o object.o ball.o brick.o in_game.o game_over.o scoreboard.o missile.o\
          main_menu.o button.o pause_menu.o

all: Breakout

cp_functions.o: cp_functions.c
	$(CC) $(CFLAGS) -c cp_functions.c

mouse.o: mouse.cpp
	$(CXX) $(CFLAGS) -c mouse.cpp

object.o: object.cpp
	$(CXX) $(CFLAGS) -c object.cpp

ball.o: ball.cpp
	$(CXX) $(CFLAGS) -c ball.cpp

brick.o: brick.cpp
	$(CXX) $(CFLAGS) -c brick.cpp

button.o: button.cpp
	$(CXX) $(CFLAGS) -c button.cpp

main_menu.o: main_menu.cpp
	$(CXX) $(CFLAGS) -c main_menu.cpp

in_game.o: in_game.cpp
	$(CXX) $(CFLAGS) -c in_game.cpp

pause_menu.o: pause_menu.cpp
	$(CXX) $(CFLAGS) -c pause_menu.cpp

game_over.o: game_over.cpp
	$(CXX) $(CFLAGS) -c game_over.cpp

scoreboard.o: scoreboard.cpp
	$(CXX) $(CFLAGS) -c scoreboard.cpp

missile.o: missile.cpp
	$(CXX) $(CFLAGS) -c missile.cpp

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Breakout: $(OBJECTS)
	$(CXX) -o Breakout $(OBJECTS) $(LDFLAGS)

clean: 
	rm -f $(OBJECTS) Breakout CON

