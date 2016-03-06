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
    sky = 0,
    grass = 1,
    dirt = 2,
    stone = 3,
    sand = 4,
    coal = 5,
    copper = 6,
    tin = 7,
    player = 8,
    END_SPRITE = 9,
    SPRITE_SIZE = 64
};

class SpriteHandler{
public:
    //returns the instance of the handler
    static std::shared_ptr<SpriteHandler> getInstance();
    void loadImages();
    std::unique_ptr<Graphics::Image>& get(int i);
    SpriteHandler(){}; //no creation needed

private:
    //creation and singleton method blocks
    SpriteHandler(SpriteHandler const &s){}; // no copy constructor
    //SpriteHandler& operator=(SpriteHandler const &s){}; //no assignment
    //the only instance allowed
    static std::shared_ptr<SpriteHandler> instance;
    
    //actual sprite things
    std::unique_ptr<Graphics::Image> images[SPRITE_CODE::END_SPRITE];
};
#endif /* SpriteHandler_hpp */
