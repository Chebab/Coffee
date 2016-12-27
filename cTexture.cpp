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
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    texture=NULL;
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
bool cTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font* font,SDL_Renderer* gRenderer )
{
    //Get rid of preexisting texture
    this->free();
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            textWidth = textSurface->w;
            textHeight = textSurface->h;
        }
        renderer = gRenderer;
        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return texture != NULL;
}
bool cTexture::render(SDL_Renderer* gRenderer,int xpos,int ypos){
    SDL_Rect playerArea = {xpos, ypos,static_cast<int>(textWidth), static_cast<int>(textHeight)};
    SDL_RenderCopy(gRenderer, texture, NULL, &playerArea);
    return true;
}
