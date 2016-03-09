//
//  Tile.hpp
//  Project2
//
//  Created by William Meaton on 09/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <stdio.h>

class Tile{
public:
    Tile(int tc, bool solid, float strength, int itemDrop);
    int textureCode = 0, itemDrop = 0;
    float strength = 0;
    bool solid = false;

};

#endif /* Tile_hpp */
