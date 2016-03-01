//
//  MapCreationState.cpp
//  Project2
//
//  Created by William Meaton on 28/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "MapCreationState.hpp"

MapCreationState::MapCreationState(){
    iH = InputHandler::getInstance();
    wH = WorldHandler::getInstance();
}

MapCreationState::~MapCreationState(){
    
}

void MapCreationState::setup(){
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), 2);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
}

void MapCreationState::update(){
    wH->updateWorld();
    if(iH->getMOUSE0()){
        int x = iH->getMouseX();
        int y = iH->getMouseY();
        x /= SPRITE_SIZE;
        y /= SPRITE_SIZE;
        x += x*wH->getOffSetX();
        y += -y*wH->getOffSetY();
        wH->getMap()[y+x*wH->getxMapSize()];
    }
}

void MapCreationState::draw(){
    WorldHandler::getInstance()->renderWorld();
    SpriteHandler::getInstance()->get(currentTexture)->draw(iH->getMouseX(), iH->getMouseY(), SPRITE_SIZE, SPRITE_SIZE);
}

void MapCreationState::keyPressed(int key){
    if(key == 80){
        std::cout << "right" << std::endl;
        if(currentTexture < SPRITE_CODE::END_SPRITE){
            currentTexture++;
        }else{
            currentTexture = 0;
        }
    }
    if(iH->getRIGHT()){
        wH->offSetby(1, 0, true);
    }
    if(iH->getLEFT()){
        wH->offSetby(-1, 0, true);
    }
    if(iH->getDOWN()){
        wH->offSetby(0, 1, true);
    }
    if(iH->getUP()){
        wH->offSetby(0, -1, true);
    }
}