// Map.cpp


#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map(){
	mapArray 	= NULL;
	tileWidth 	= 0;
	tileHeight 	= 0;
	mapWidth 	= 0;
	mapHeight 	= 0;
}
Map::~Map(){
    this->free();
}
Map::Map(std::string inFile){
    string line;
    
    printf("filename: %s\n",inFile.c_str());
    
    ifstream mapfile(inFile,ios::in);
    
    mapWidth  = DEFAULT_MAP_WIDTH* TILE_SIZE;
    mapHeight = DEFAULT_MAP_HEIGHT * TILE_SIZE;
    tileWidth 	= DEFAULT_MAP_WIDTH;
    tileHeight 	= DEFAULT_MAP_HEIGHT;
    
    mapArray = tileMap(tileWidth, tileHeight);
    
    int tileNum = -1;
    if (mapfile.is_open()){
        
        printf("Loading map:\n");
        for (int i=0; i<tileHeight; i++) {
            
            tileNum = -1;
            for (int j = 0; j<tileWidth; j++) {
                mapfile >> tileNum;
                //printf("Number of textures: %d\n", (int)tile_texture.size());
                if (tileNum < tile_texture.size() && tileNum >= 0) {
                    printf("%d ",tileNum);
                    Tile *tile = getTile(j, i);
                    if (tile) {
                        SDL_Texture* temp = tile_texture[tileNum]->getTexture();
                        tile->setTexture(temp);
                        if (tileNum > 0) {
                            tile->setWalkable(false);
                        }
                    }
                    else{
                        printf("tile (%d,%d) not found\n",j,i);
                    }
                    
                }
                else {
                    printf("X ");
                }
            }
            printf("\n");
        }
        
        mapfile.close();
    }
    
    setStartingTile(0, 0);
    
}

Map::Map(unsigned int width, unsigned int height) {
    //TODO: Handle the case where width or height is 0
	mapWidth  = width * TILE_SIZE;
	mapHeight = height * TILE_SIZE;
	tileWidth 	= width;
	tileHeight 	= height;
    
    
    mapArray = tileMap(width, height);
	//cout << "setting the tiles worked" << endl;
    setStartingTile(0, 0);
}

Tile** Map::tileMap(unsigned int width,unsigned int height)
{
    
    // TODO: The map is flipped, x is y and vice versa
    // mapArray -> [ptr1],[ptr2],[ptr3],[ptr4],[ptr5]
    // ptr1 -> array1	^
    // ptr2 -> array2	|
    // ptr3 -> array3	|
    // ptr4 -> array4	|
    // ptr5 -> array5	v height
    // 		   <----> width
    Tile** m_arr  = new Tile *[height];
    for (int i = 0; i <height; i++) {
        m_arr[i] = new Tile[width];
    }
    
    
    // Loop for setting the position of all the Tiles
    int xpos = 0, ypos = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++){
            m_arr[i][j] = Tile(xpos,ypos,true);
            xpos += TILE_SIZE;
        }
        xpos = 0;
        ypos += TILE_SIZE;
    }
    return m_arr;
}


// get the Neighbours of the chosen tile
vector<Tile*> Map::getNeighbours(int xpos, int ypos){
    vector<Tile*> neighbours;
    
    /*
    The layout of the tiles
     1 2 3
     4 * 5
     6 7 8
     Should turn into
     [1 2 3 4 5 6 7 8]
     */
    
    // Get the pointer to tile 1
    //x direction: --->
    for (int xDir=xpos-1; xDir<=xpos+1; xDir++) {
        for (int yDir=ypos-1; yDir<=ypos+1; yDir++) {
            if (!(xDir==xpos && yDir==ypos)) {
                neighbours.push_back(getTile(xDir, yDir));
            }
        }
    }
    
    
	return neighbours;
}

vector<Tile*> Map::getNeighbours(Tile* ptr){
    
    if (ptr==NULL) {
        vector<Tile*> returnList;
        return returnList;
    }
    return getNeighbours(ptr->getXindex(), ptr->getYindex());
}

// Get the numbered tile
Tile* Map::getTile(int xpos, int ypos){
	//Tile *temp;
	if(xpos > (tileWidth-1) || ypos > (tileHeight - 1) || ypos < 0 || xpos < 0){
		//cout << "getTile is giving me null, tileWidth is " << tileWidth<< " xpos is " << xpos << endl;
		return NULL;
	}
	return &mapArray[ypos][xpos];
}

// Get a tile from coordinates
Tile* Map::getTileFromPos(int xpos, int ypos){
	return getTile(xpos/TILE_SIZE, ypos/TILE_SIZE);
}

bool Map::setStartingTile(unsigned int x,unsigned int y){
    if (x<tileWidth && y<tileHeight) {
        startingTiles.push_back(&mapArray[x][y]);
        return true;
    }
    return false;
}

// Set a new Tile in the map
void Map::setTile(Tile &tile, int xpos, int ypos){
	mapArray[ypos][xpos] = tile;
}

vector<Tile*> Map::getStartingTiles(){
    return this->startingTiles;
}

Tile* Map::initTile(){
    return startingTiles[0];
}
// Deallocate the Map
void Map::free(){
    //startingTiles.~vector();
    if (mapArray==NULL) {
        return;
    }
	// free dynamically allocated memory
	for( int i = 0 ; i < tileHeight; i++ ){
    	delete [] mapArray[i]; // delete array within matrix
	}
	// delete actual matrix
	delete[] mapArray;

	// dereferencing the map
	mapArray = NULL;
    
}

/*
int main(int arg, char **argv) {
	int xsize = 11;
	int ysize = 10;
	Map map = Map(xsize, ysize);
	//bool empty = map.getTile(5,0).isEmpty();
	cout << "initialization went well" << endl;

	if(map.getTile(6,6) == NULL) {
		cout << "getTile works" << endl;
	}
	Tile* tile1 = NULL;

	for(int i = 0; i < ysize; i++){
		cout << i << endl;
		for(int j = 0; j<xsize; j++){
			tile1 = map.getTile(j,i);
			//cout << "ok" << endl;
			if(tile1 == NULL){
			//printf("Could not get tile " + i + "," +j"\n");
				cout << "Could not get tile " << i << "," << j << endl;
			}
			else{
			cout << " (" << tile1 -> getXpos() 
				<< "," << tile1 -> getYpos() << ") ";
			}
		}
		//cout << "loop i went well" << endl;
	}
	cout << "entire loop went well" << endl;
	map.free();
	cout << "free went well" << endl;
	//cout << "It worked! The tile is " << empty << endl;
}
*/
