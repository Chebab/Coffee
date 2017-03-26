// Tile.h


#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Shapes.h"
#include "texture_info.h"
static const int TILE_SIZE 	= 32;
//static const int INT_MAX	= 65535;

class Tile {
private:
    //TODO: Tiles should not retain any information about what position it has
	int xCoordinate;
	int yCoordinate;
	bool isNull;
    
	SDL_Texture* text;
	bool walkable;
	

public:
Tile (){
	isNull = true;
	text = NULL;
	walkable =false;
	
}
~Tile (){
	free();
}

Tile (int xpos, int ypos, bool walk){
	isNull = false;
	walkable = walk;
	xCoordinate = xpos;
	yCoordinate = ypos;
	text = NULL;
}
Tile (int xpos, int ypos, bool walk,SDL_Texture* txr){
    isNull = false;
    walkable = walk;
    xCoordinate = xpos;
    yCoordinate = ypos;
    text = txr;
}
    
Tile(Tile& tile){
    xCoordinate=tile.xCoordinate;
    yCoordinate=tile.yCoordinate;
    isNull=tile.isNull;
    text=tile.text;
    walkable=tile.walkable;
}
    
Tile(Tile& tile,int xpos,int ypos,bool walk){
    xCoordinate=xpos;
    yCoordinate=ypos;
    isNull=tile.isNull;
    text=tile.text;
    walkable=walk;
}

int getXpos() {
	return xCoordinate;
}
int getYpos() {
	return yCoordinate;
}
int getXindex(){
    return xCoordinate/TILE_SIZE;
}
int getYindex(){
    return yCoordinate/TILE_SIZE;
}
bool isEmpty() {
	return isNull;
}

void setTexture(SDL_Texture* txr){
	text = txr;
}
bool isWalkable(){
	return walkable;
}

void setWalkable(bool beWalkable){
    walkable=beWalkable;
}

    
Point getPos(){
    return Point(this->xCoordinate, this->yCoordinate);
}
    
Rectangle getBoundries(){
    return Rectangle(this->getPos(),TILE_SIZE);
}

SDL_Texture* getTexture(){
	return text;
}

void renderer(SDL_Renderer* gRend, int cameraXpos, int cameraYpos){
	// TODO make sure that this very operation is done in camera instead
	SDL_Rect temp = { xCoordinate - cameraXpos, yCoordinate - cameraYpos, TILE_SIZE, TILE_SIZE};
	SDL_RenderCopy(gRend, text, NULL, &temp);
}

static bool checkIfNULL(Tile* target){
	if (target == NULL){
		return true;
	}
	return false;
}

void free(){
	xCoordinate = 0;
	yCoordinate = 0;
	isNull = true;
	text = NULL;
    walkable = false;
}

};

#endif
