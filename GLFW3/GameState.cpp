//
//  GameState.cpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState(){
    //load world and sprites at the same time
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), 2);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
    
    worldHandler = WorldHandler::getInstance();
    //add the player to the render and update loop
    worldHandler->addToQueues(&player);
    worldHandler->addToQueues(&t);
}

void GameState::update(){
    worldHandler->updateWorld();
}

void GameState::draw(){
    worldHandler->renderWorld();
}