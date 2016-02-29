//
//  MenuState.cpp
//  Project2
//
//  Created by William Meaton on 29/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "MenuState.hpp"

void MenuState::setup(){
    
}

MenuState::~MenuState(){
    delete gameState;
    gameState = nullptr;
    delete mapCreationState;
    mapCreationState = nullptr;
}

void MenuState::setup(){
    gameState = new GameState();
    mapCreationState = new MapCreationState();
    
}

void MenuState::update(){
    if(InputHandler::getInstance()->getLEFT()){
        
    }
}

void MenuState::draw(){
    
}

