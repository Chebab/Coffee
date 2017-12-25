// Map

#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>
#include "tile_info.h"

#define DEFAULT_MAP_HEIGHT 5
#define DEFAULT_MAP_WIDTH 5
using namespace std;
class Map {
private:
	Tile **mapArray;
	unsigned int tileWidth, tileHeight;
	int mapWidth, mapHeight;
    vector<Tile*> startingTiles;
    
    Tile** tileMap(unsigned int,unsigned int);

public:
	Map();
	~Map();
    Map(std::string inFile);
    Map(unsigned int, unsigned int);
	vector<Tile*> getNeighbours(int, int);
    vector<Tile*> getNeighbours(Tile*);
	Tile* getTile(int,int);
	void setTile(Tile &tile,int,int);
    bool setStartingTile(unsigned int, unsigned int);
    
    vector<Tile*> getStartingTiles();
    Tile* initTile();
	Tile* getTileFromPos(int, int);
	void free();
};
#endif
