CC = mingw32-gcc
CXX = mingw32-g++

CFLAGS = -IC:\CodeBlocks32\MinGW\include
LDFLAGS = -LC:\CodeBlocks32\MinGW\lib -lmingw32 -lSDLmain -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lopengl32 -lglu32

all: Breakout.exe

cp_functions.o: cp_functions.c
	$(CXX) $(CFLAGS) -c cp_functions.c

main.o: main.c
	$(CXX) $(CFLAGS) -c main.c

Breakout.exe: cp_functions.o main.o
	$(CXX) -o Breakout.exe cp_functions.o main.o $(LDFLAGS)

clean: 
	rm -f *.o Breakout.exe

