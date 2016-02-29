//
//  MapCreationState.cpp
//  Project2
//
//  Created by William Meaton on 28/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "MapCreationState.hpp"

MapCreationState::MapCreationState(){

}

MapCreationState::~MapCreationState(){
    
}

void MapCreationState::setup(){
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), 2);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
}

void MapCreationState::update(){
    WorldHandler::getInstance()->updateWorld();
    if(InputHandler::getInstance()->getMOUSE0()){
        int x = InputHandler::getInstance()->getMouseX();
        int y = InputHandler::getInstance()->getMouseY();
        x /= SPRITE_SIZE;
        y /= SPRITE_SIZE;
        x += x*WorldHandler::getInstance()->getOffSetX();
        y += y*WorldHandler::getInstance()->getOffSetY();
        std::cout << x << " " << y << std::endl;
    }
    
    if(InputHandler::getInstance()->getRIGHT()){
        WorldHandler::getInstance()->offSetby(1, 0, true);
    }
    if(InputHandler::getInstance()->getLEFT()){
        WorldHandler::getInstance()->offSetby(-1, 0, true);
    }
}

void MapCreationState::draw(){
    WorldHandler::getInstance()->renderWorld();
}