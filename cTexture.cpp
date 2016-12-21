//
//  cTexture.cpp
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2016-07-24.
//  Copyright © 2016 Viktor Johansson. All rights reserved.
//


#include "cTexture.h"

cTexture::cTexture(){
    texture     = NULL;
    textWidth   = 0;
    textHeight  = 0;
}
cTexture::~cTexture(){
    free();
}

void cTexture::free(){
    textHeight  = 0;
    textWidth   = 0;
    if (!texture) {
        SDL_DestroyTexture(texture);
    }
}

bool cTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer){
    // Free any preexisting texture
    free();
    
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    
    }
    else
    {
        //Get image dimensions
        textWidth = loadedSurface->w;
        textHeight = loadedSurface->h;
        
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    renderer = gRenderer;
    texture = newTexture;
    return newTexture != NULL;
}