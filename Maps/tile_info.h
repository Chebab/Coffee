//
//  tile_info.h
//  Coffe_Quest
//
//  Created by Viktor Johansson on 2016-12-30.
//  Copyright © 2016 Viktor Johansson. All rights reserved.
//

#ifndef tile_info_h
#define tile_info_h

#include "Tile.h"
#include "texture_info.h"

enum tile_type{
    grass_tile,
    wall_tile
};

static std::vector<Tile> tiles;

#endif /* tile_info_h */
