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

enum TILES{
    T_sky = 0,
    T_grass = 1,
    T_dirt = 2,
    T_stone = 3,
    T_sand = 4,
    T_coal = 5,
    T_copper = 6,
    T_tin = 7,
    T_destruction1 = 8,
    T_destruction2 = 9,
    T_destruction3= 10
};

class Tile{
public:
    Tile(int id, int textureCode, bool solid, float strength, int itemDrop);
    //id is this tiles Id
    //textureCode is the texture code that it draws
    //itemDrop is the itemID that this tile will drop when destroyed
    int id = -1, textureCode = -1, itemDrop = -1;
    float strength = 0;
    bool solid = false;

};

#endif /* Tile_hpp */
