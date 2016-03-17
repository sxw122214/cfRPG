//
//  MenuState.cpp
//  Project2
//
//  Created by William Meaton on 29/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "MenuState.hpp"

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
        gameState->setup();
        State::setState(gameState);
    }
    if(InputHandler::getInstance()->getRIGHT()){
        mapCreationState->setup();
        State::setState(mapCreationState);
    }
}

void MenuState::draw(){
    text.draw("Press Left to go to the game, Right to go to the map editor", WorldHandler::getInstance()->windowWidth/2, WorldHandler::getInstance()->windowHeight/2);
}

