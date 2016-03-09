//
//  Item.hpp
//  Project2
//
//  Created by William Meaton on 09/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>

class Item{
public:
    Item(int id, int textureCode, bool placeable, int tileID);
    //id is this Item's id
    //textureCode is the texture that will represent this
    //tileId is the tile that will be placed if this is placed
    int id = -1, textureCode = -1, tileID = -1;
    //if this item can be placed or not
    bool placeable = false;
};


#endif /* Item_hpp */
