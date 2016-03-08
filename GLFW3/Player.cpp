//
//  Player.cpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#include "Player.hpp"

Player::Player(const Math::Vector2D &scene, const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible): GameObject(scene, position, bounds, visible){
    worldHandler = WorldHandler::getInstance();
    inputHandler = InputHandler::getInstance();
}

void Player::update(){
    this->gravity(true);
    bool movement = false;
    Math::Vector2D sv(0, 0);
    //on player movement
    if(inputHandler->getDOWN()){
        sv.y += speed;
        movement = true;
    }
    if(inputHandler->getUP()){
        sv.y += -speed;
        movement = true;
    }
    if(inputHandler->getRIGHT()){
        sv.x += speed;
        movement = true;
    }
    if(inputHandler->getLEFT()){
        sv.x += -speed;
        movement = true;
    }
    //do the movement given from the player
    worldHandler->movementCheck(editPosition(), sv, editScene(), true, true);
    
    
    
    //you can't mind whilst moving
    if(!movement){
        //to start mining
        if(inputHandler->getMOUSE0() && !mining){
            mining = true;
            timer.start();
        }
        //if you're currently mining then check
        if(mining){
            //if the mouse is still being pressed
            if(!inputHandler->getMOUSE0()){
                mining = false;
                std::cout << "unclicked" << std::endl;
                timer.reset();
            }else{
                //and if the timer is up
                if(timer.elapsedTime() >= 1){
//                    wordsldHandler->getTile(inputHandler->getMouseX(), inputHandler->getMouseY()) = &worldHandler->getTiles()[0];
                    timer.reset();
                    mining = false;
                }
            }
        }
    }else{
        std::cout << "you moved" << std::endl;
        mining = false;
        timer.reset();
    }
}

void Player::render(){
    SpriteHandler::getInstance()->get(SPRITE_CODE::player)->draw(this->getPosition());
}