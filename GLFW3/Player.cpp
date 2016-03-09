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
    bool movement = false;
//    this->gravity();
    editVelocity() = editVelocity() - 2;
    //on player movement
    if(inputHandler->getDOWN()){
        editVelocity().y += speed;
    }
    if(inputHandler->getUP()){
        editVelocity().y += -speed;
    }
    if(inputHandler->getRIGHT()){
        editVelocity().x += speed;
    }
    if(inputHandler->getLEFT()){
        editVelocity().x += -speed;
    }
    if(inputHandler->getSPACE() && getVelocity().y == 0){
        editVelocity().y += -speed*2;
    }
    if(getVelocity().x != 0 && getVelocity().y != 0){
        //do the movement given from the player
        std::cout << getVelocity().x << " " << getVelocity().y << std::endl;
        worldHandler->movementCheck(editPosition(), editVelocity(), editScene(), true, true);
        movement = true;
    }else{
        movement = false;
    }
    
    //you can't mine whilst moving
    if(!movement){
        //if the LMB is pressed and you're not already mining, start the checks to start mining
        if(inputHandler->getMOUSE0() && !mining){
            
            //get the distance between the mouse and the player
            float distance = Math::vectorDistance(getPosition().x+SPRITE_SIZE/2, getPosition().y+SPRITE_SIZE/2, inputHandler->getMouseX(), inputHandler->getMouseY());
            
            //only if the distance is less than the spritesize*3 then we should start mining
            if(distance < SPRITE_SIZE*3){
                mining = true;
                timer.start();
            }
        }
        //if you're currently mining then check you're still holding that LMB
        if(mining){
            //if the mouse isn't being pressed
            if(!inputHandler->getMOUSE0()){
                mining = false;
                timer.reset();
            }else{
                //if you've been mining for the right amount of time... this will be changed per block soon
                if(timer.elapsedTime() >= 1){
                    worldHandler->getTile(inputHandler->getMouseX(), inputHandler->getMouseY()) = &worldHandler->getTiles()[0];
                    timer.reset();
                    mining = false;
                }
            }
        }
    }else if(mining){
        std::cout << "you moved" << std::endl;
        mining = false;
        timer.reset();
    }
}

void Player::render(){
    SpriteHandler::getInstance()->get(SPRITE_CODE::player)->draw(this->getPosition());
}