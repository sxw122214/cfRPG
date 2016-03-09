//
//  GameState.cpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState(){

}

void GameState::setup(){
    //load world and sprites at the same time
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), 3);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
    
    worldHandler = WorldHandler::getInstance();
    //add the player to the render and update loop
    pushBothRU(&player);
    pushBothRU(&t);
}

void GameState::update(){
    t.talk(&player);
    for(auto go : updateVector){
        go->update();
    }
}

void GameState::draw(){
    worldHandler->renderWorld();
    for(auto go : renderVector){
        go->render();
    }
}

void GameState::pushBothRU(GameObject *go){
    renderVector.push_back(go);
    updateVector.push_back(go);
}