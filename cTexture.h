//
//  cTexture.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2016-07-24.
//  Copyright © 2016 Viktor Johansson. All rights reserved.
//

#ifndef cTexture_h
#define cTexture_h
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
class cTexture{
private:
    SDL_Texture* texture;
    // Maybe include possibility to have several renderers
    SDL_Renderer* renderer;
    unsigned int textHeight;
    unsigned int textWidth;
public:
    cTexture();
    ~cTexture();
    
    SDL_Texture* getTexture(){
        return texture;
    }
    unsigned int getHeight(){
        return textHeight;
    }
    unsigned int getWidth(){
        return textWidth;
    }
    
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
#ifdef _SDL_TTF_H
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
#endif
    void free();
    
};

#endif /* cTexture_h */
