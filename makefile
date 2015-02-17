CC = g++
SHAPES = Shapes/Point.cpp Shapes/Circle.cpp Shapes/Line.cpp Shapes/2DVectorMath.cpp
WORKING_SHAPES = Shapes/Point.cpp Shapes/Circle.cpp Shapes/Line.cpp Shapes/2DVectorMath.cpp
LINKER = -lSDL2 -lSDL2_image

all: Main.o

Map.o:
	g++ Map.cpp Tile.cpp -o Map $(LINKER)

Main.o:
	g++ main.cpp camera.cpp Maps/Map.cpp -o main $(LINKER)

Shapes.o:
	g++ Shapes/testShapes.cpp $(SHAPES) -o testShapes