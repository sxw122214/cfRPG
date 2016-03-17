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
}

void MenuState::update(){
    //make sure there is an actual selection
    if(selection.size() == 0){
        return;
    }
    //go to the next state with the users selection
    if(InputHandler::getInstance()->getLEFT()){
        gameState = new GameState(atoi(selection.c_str()));
        gameState->setup();
        State::setState(gameState);
    }
    if(InputHandler::getInstance()->getRIGHT()){
        mapCreationState = new MapCreationState(atoi(selection.c_str()));
        mapCreationState->setup();
        State::setState(mapCreationState);
    }
}

void MenuState::draw(){
    glColor4d(0, 0, 0, 1);
    int width = WorldHandler::getInstance()->windowWidth, height = WorldHandler::getInstance()->windowHeight;
    //draw the menu text!
    text.draw("Press Left to go to the game, Right to go to the map editor", width*0.25, (height/2)-210);
    text.draw("But first! We require a level number to be loaded/created", width*0.25, (height/2)-140);
    text.draw("Type the world number now! - " + selection, width*0.25, (height/2)-70);
    text.draw("When in game you can use 't' to save the world!", width*0.25, (height/2));
    text.draw("Use WASD, arrow keys and space to move around", width*0.25, (height/2)+70);
    text.draw("Click and hold the left mouse button to mine blocks", width*0.25, (height/2)+140);
    text.draw("E and Q to cycle items and the right mouse button to place", width*0.25, (height/2)+210);
    glColor4d(1, 1, 1, 1);
}

void MenuState::keyPressed(int key){
    if(key == GLFW_KEY_BACKSPACE && selection.size() > 0){
        selection = selection.substr(0, selection.size()-1);
    }
    if(key >= 48 && key <= 57 && selection.size() <=10){
        selection += std::to_string(key-48);
    }
}
