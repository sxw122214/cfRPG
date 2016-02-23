//
//  Core.cpp
//  GLFW3
//
//  Created by William Meaton on 08/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#include "Core.hpp"
//for graphics
using namespace Graphics;

Core::~Core(){
    delete gameState;
    gameState = nullptr;
    delete mapState;
    mapState = nullptr;
    inputHandler = nullptr;
}

void Core::setup(){
    //this needs to be set here otherwise c
    inputHandler = InputHandler::getInstance();
    
    //initialise the state
    gameState = new GameState();
    mapState = new MapCreationState();
    //set the current state to the game
    State::setState(gameState);
    
    //set the windowHeight, windoWidth
    WorldHandler::getInstance()->windowHeight = Runner::windowHeight;
    WorldHandler::getInstance()->windowWidth = Runner::windowWidth;
    Graphics::setBackground(0, 128, 128, 255);
}

void Core::update(){
    State::getCurrentState()->update();
    inputHandler->mouseInput(mouseX, mouseY);
}

void Core::draw(){
    State::getCurrentState()->draw();
}

void Core::keyPressed(int key){
    //0 - 48
    //9 - 57
    std::cout << true <<std::endl;
    inputHandler->keyDown(key);
}

void Core::keyReleased(int key){
    inputHandler->keyUp(key);
}

void Core::mousePressed(int button){
    inputHandler->mouseDown(button);
}

void Core::mouseReleased(int button){
    inputHandler->mouseUp(button);
}