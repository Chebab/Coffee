//Player class

#ifndef PLAYER_H
#define PLAYER_H
#include "Map.h"

static const int PLAYER_RADIUS = 16;
class Player{
private:
	int xpos;
	int ypos;
	int xVelocity;
	int yVelocity;
	//The map the player is currently on
	Map* currentMap;
	//The Tile the player is currently standing on
	Tile* tilePosition;
	//Visualization of the player
	SDL_Texture* visualPlayer;

public:
	Player(){
		currentMap = NULL;
		position = NULL;
		visualPlayer = NULL;
	}
	~Player(){
		currentMap = NULL;
		position = NULL;
		visualPlayer = NULL;
	}
	Player(int startingXpos, int startingYpos, Map* map, Tile* startingTilePos, SDL_Texture texture){
		xpos = startingXpos;
		ypos = startingYpos;
		xVelocity = 0;
		yVelocity = 0;
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

	bool checkIfNotNULL(Tile){

	}
	void moveOnTile(){
		bool moveOnX = true;
		bool moveOnY = true;
		Tile* targetTile = NULL;
		int newXpos = xpos + PLAYER_RADIUS + xVelocity;
		int newYpos = ypos + PLAYER_RADIUS + yVelocity;
		

		//Check on the x-axis
		targetTile = currentMap -> getTileFromPos(newXpos, ypos);
		if (targetTile == NULL){
			moveOnX = false;
		}
		else{
			moveOnX = moveOnX & targetTile -> isWalkable();
		}

		//Check on the y-axis

		targetTile = currentMap -> getTileFromPos(xpos, newYpos);
		if (targetTile == NULL){
			moveOnY = false;
		}
		else {
			moveOnY = moveOnY & targetTile -> isWalkable();
		}
		

		//Check the final position
		targetTile = currentMap -> getTileFromPos(newXpos, newYpos);
		if (targetTile == NULL){
			moveOnX = false;
			moveOnY = false;
		}
		else{

		}

	}

};


#endif