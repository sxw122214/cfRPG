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
    delete menuState;
    menuState = nullptr;
    inputHandler = nullptr;
}

void Core::setup(){
    //set the windowHeight, windoWidth
    WorldHandler::getInstance()->windowHeight = Runner::windowHeight;
    WorldHandler::getInstance()->windowWidth = Runner::windowWidth;
    
    //this needs to be set here otherwise c
    inputHandler = InputHandler::getInstance();
    
    gameState = new GameState();
    menuState = new MenuState();
    mapCreationState = new MapCreationState();
    
    //initialise the state
    //set the current state to the game
    State::addState(menuState);
    State::addState(gameState);
    State::addState(mapCreationState);
    
    //call setup
    State::getCurrentState()->setup();
    Graphics::setBackground(255, 255, 255, 255);
}

void Core::update(){
    State::getCurrentState()->update();
    inputHandler->mouseInput(mouseX, mouseY);
    inputHandler->joyStick();
}

void Core::draw(){
    State::getCurrentState()->draw();
}

void Core::exitCalled(){
    State::getCurrentState()->exitCalled();
}

void Core::keyPressed(int key){
    inputHandler->keyDown(key);
    State::getCurrentState()->keyPressed(key);
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