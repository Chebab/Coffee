// Map

#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map {
private:
	Tile **mapArray;
	int tileWidth, tileHeight;
	int mapWidth, mapHeight;

public:
	Map();
	//~Map();
	Map(int, int);
	Tile* getNeighbours(int, int);
	Tile* getTile(int,int);
	void setTile(Tile,int,int);
	Tile* getTileFromPos(int, int);
	void free();
};
#endif