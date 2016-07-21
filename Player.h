//
//  Player.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-12-27.
//  Copyright © 2015 Viktor Johansson. All rights reserved.
//
#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"
#include "Shapes.h"


static const int PLAYER_RADIUS = TILE_SIZE/2;
class Player{
private:
	float xpos;
	float ypos;
	//The map the player is currently on
	Map* currentMap;
	//The Tile the player is currently standing on
	Tile* tilePosition;
	//Visualization of the player
	SDL_Texture* visualPlayer;

public:
	Player(){
		currentMap = NULL;
		visualPlayer = NULL;
        xpos = 0;
        ypos = 0;
	}
	~Player(){
		currentMap = NULL;
		visualPlayer = NULL;
        tilePosition = NULL;
	}
	Player(float startingXpos, float startingYpos, Map* map, Tile* startingTilePos, SDL_Texture* texture){
		xpos = startingXpos;
		ypos = startingYpos;
		currentMap = map;
		tilePosition = startingTilePos;
		visualPlayer = texture;
	}

	int getXpos(){
		return xpos;
	}
	int getYpos(){
		return ypos;
	}

	bool checkIfNotNULL(Tile&){
        return false;
	}
    
    bool movePlayer(float xVelo, float yVelo);
    
    void render(SDL_Renderer* gRenderer){
        SDL_Rect playerArea = {(int)xpos-PLAYER_RADIUS, (int) ypos-PLAYER_RADIUS,TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(gRenderer, visualPlayer, NULL, &playerArea);
    }

};


#endif