CC = gcc
CXX = gcc

CFLAGS = -std=c99
LDFLAGS = -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_image -lSDL_mixer -framework Cocoa -framework OpenGL

all: Breakout

cp_functions.o: cp_functions.c
	$(CXX) $(CFLAGS) -c cp_functions.c

main.o: main.c
	$(CXX) $(CFLAGS) -c main.c

Breakout: cp_functions.o main.o
	$(CXX) -o Breakout cp_functions.o main.o $(LDFLAGS)

clean: 
	rm -f *.o Breakout

