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

//#define TEXNAME "hej"
static cTexture* grass        = new cTexture();
static cTexture* orangeRect   = new cTexture();
static cTexture* playPic      = new cTexture();
static cTexture* fpsText      = new cTexture();

static std::vector<std::string> tile_texture_files =
{
    "Textures/grass.png",               // Grass texture
    "Textures/64x64_rect_orange.png"    // Block
};

// Instead of textures, make sure that different tiles are represented (perhaps add copy method)
static std::vector<cTexture> tile_texture;


enum tile_texture_num {
    grass_tile,
    wall_tile
};

#endif /* texture_info_h */
