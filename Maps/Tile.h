// Tile.h


#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const int TILE_SIZE 	= 32;
//static const int INT_MAX	= 65535;

class Tile {
private:
	int xCoordinate;
	int yCoordinate;
	bool isNull;
	SDL_Texture* text;
	bool walkable;
	//SDL_Rect* sqr;

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

int getXpos() {
	return xCoordinate;
}
int getYpos() {
	return yCoordinate;
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
}

};

#endif