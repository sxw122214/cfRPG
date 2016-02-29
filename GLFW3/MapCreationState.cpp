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
}

void MapCreationState::draw(){
    WorldHandler::getInstance()->renderWorld();
}