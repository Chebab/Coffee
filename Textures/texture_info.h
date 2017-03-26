//
//  texture_info.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2016-12-29.
//  Copyright © 2016 Viktor Johansson. All rights reserved.
//

#ifndef texture_info_h
#define texture_info_h
#include "cTexture.h"



//#define TEXTURE_DIR "Textures/"
static cTexture* grass        = new cTexture();
static cTexture* orangeRect   = new cTexture();
static cTexture* playPic      = new cTexture();
static cTexture* fpsText      = new cTexture();

static std::vector<std::string> tile_texture_files =
{
    "Textures/grass.png",               // Grass texture
    "Textures/64x64_rect_orange.png"    // Block
};


// Contains all the player textures
static std::vector<std::string> player_texture_files =
{
    "Textures/32x32_player.png"         // Player main pic
};

// Instead of textures, make sure that different tiles are represented (perhaps add copy method)
static std::vector<cTexture*> tile_texture;
static std::vector<cTexture*> player_texture;


enum tile_texture_num {
    i_grass = 0,
    i_wall
};

#endif /* texture_info_h */
