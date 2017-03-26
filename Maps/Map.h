// Map

#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>
#include "tile_info.h"
using namespace std;
class Map {
private:
	Tile **mapArray;
	unsigned int tileWidth, tileHeight;
	int mapWidth, mapHeight;
    vector<Tile*> startingTiles;

public:
	Map();
	~Map();
    Map(std::string inFile);
    Map(unsigned int, unsigned int);
	vector<Tile*> getNeighbours(int, int);
    vector<Tile*> getNeighbours(Tile*);
	Tile* getTile(int,int);
	void setTile(Tile,int,int);
    bool setStartingTile(unsigned int, unsigned int);
    
    vector<Tile*> getStartingTiles();
    Tile* initTile();
	Tile* getTileFromPos(int, int);
	void free();
};
#endif
