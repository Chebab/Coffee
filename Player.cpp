//
//  Player.cpp
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2015-12-27.
//  Copyright © 2015 Viktor Johansson. All rights reserved.
//

#include <stdio.h>
#include "Player.h"
using namespace std;
bool Player::movePlayer(float xVelo, float yVelo){
    //Check if the player is standing on a map and a tile
    // Should most likely be removed for efficiency reasons
    if (currentMap == NULL || tilePosition == NULL) {
        return false;
    }
    
    vector<Tile*> neighbours = this->currentMap->getNeighbours(this->tilePosition);
    // First test if the player can move in x-direction
    Circle playerBounds = Circle(xpos+xVelo, ypos+yVelo, PLAYER_RADIUS);
    
    
    // Check if the player can move in x-direction
    for (int i = 0; i<neighbours.size(); i++) {
        Tile* tilePtr = neighbours[i];
        if (tilePtr!=NULL) {
            if (!(tilePtr->isWalkable())) {
                Rectangle tileBounds = tilePtr->getBoundries();
                if (playerBounds.Intersect(tileBounds)) {
                    playerBounds.setXpos(xpos);
                    playerBounds.setXpos(ypos);
                    break;
                }
            }
        }
    }
    // Set the new position
    xpos=playerBounds.getXpos();
    ypos=playerBounds.getYpos();
    
    // Update the tile position
    tilePosition = currentMap->getTileFromPos(xpos, ypos);
    if ((xVelo!=0 || yVelo!=0) && false) {
            cout << "(" << tilePosition->getXpos()/TILE_SIZE << "," << tilePosition->getYpos()/TILE_SIZE << ")\n" << endl;
    }
    
    
    
    return true;
}