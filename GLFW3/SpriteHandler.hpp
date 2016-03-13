//
//  SpriteHandler.hpp
//  Project2
//
//  Created by William Meaton on 20/01/2016.
//
//

#ifndef SpriteHandler_hpp
#define SpriteHandler_hpp

#include <stdio.h>
#include "CoreMain.h"
#include <memory>
enum SPRITE_CODE{
    S_sky = 0,
    S_grass = 1,
    S_dirt = 2,
    S_stone = 3,
    S_sand = 4,
    S_coal = 5,
    S_copper = 6,
    S_tin = 7,
    S_destruction1 = 8,
    S_destruction2 = 9,
    S_destruction3= 10,
    S_player = 11,
    END_SPRITE = 12,
    SPRITE_SIZE = 32
};

class SpriteHandler{
public:
    //returns the instance of the handler
    static std::shared_ptr<SpriteHandler> getInstance();
    //loads all the images in the SPRIT_CODE enum using "S_i.png" syntax
    void loadImages();
    //returns the unique pointers to the loaded sprite
    std::unique_ptr<Graphics::Image>& get(int i);
    SpriteHandler(){};

private:
    //creation and singleton method blocks
    SpriteHandler(SpriteHandler const &s){}; // no copy constructor
    SpriteHandler& operator=(SpriteHandler const &s){ return *this; }; //no assignment
    
    //the only instance allowed
    static std::shared_ptr<SpriteHandler> instance;
    
    //the array of images
    std::unique_ptr<Graphics::Image> images[SPRITE_CODE::END_SPRITE];
};
#endif /* SpriteHandler_hpp */
