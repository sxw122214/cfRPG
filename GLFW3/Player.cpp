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
    Math::Vector2D sv;
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
//    std::cout << sv.x << " " << sv.y << std::endl;
    worldHandler->movementCheck(editPosition(), sv, editScene(), true, true);
    
//    if(inputHandler->getSPACE() && getVelocity().y == 0){
//        sv.y += -speed*2;
//    }
//    if(getVelocity().x != 0 && getVelocity().y != 0){
//        //do the movement given from the player
//        std::cout << getVelocity().x << " " << getVelocity().y << std::endl;
//        movement = true;
//    }else{
//        movement = false;
//    }
    
    //you can't mine whilst moving
    if(!movement){
        //if the LMB is pressed and you're not already mining, start the checks to start mining
        if(inputHandler->getMOUSE0() && !mining){
            
            //get the distance between the mouse and the player
            float distance = Math::vectorDistance(getPosition().x+SPRITE_SIZE/2, getPosition().y+SPRITE_SIZE/2, inputHandler->getMouseX(), inputHandler->getMouseY());
            
            //only if the distance is less than the spritesize*3 then we should start mining
            if(distance < SPRITE_SIZE*3){
                miningTime = worldHandler->getTile(inputHandler->getMouseX(), inputHandler->getMouseY())->strength;
                miningType = worldHandler->getTile(inputHandler->getMouseX(), inputHandler->getMouseY())->textureCode;
                miningX = inputHandler->getMouseX()/SPRITE_SIZE;
                miningY = inputHandler->getMouseY()/SPRITE_SIZE;
                miningX*=SPRITE_SIZE;
                miningY*=SPRITE_SIZE;

                mining = true;
                timer.start();
            }
        }
        //if you're currently mining then check you're still holding that LMB
        if(mining){
            
            int x = inputHandler->getMouseX()/SPRITE_SIZE;
            int y = inputHandler->getMouseY()/SPRITE_SIZE;
            x*=SPRITE_SIZE;
            y*=SPRITE_SIZE;
            
            //check if you're still on the original tile
            if(x != miningX || y!= miningY){
                this->stopMining();
            }else if(!inputHandler->getMOUSE0()){
                this->stopMining();
            }else{
                //if the mining is still happening
                if(timer.elapsedTime() >= miningTime){
                    worldHandler->getTile(inputHandler->getMouseX(), inputHandler->getMouseY()) = &worldHandler->getTiles()[0];
                    this->stopMining();
                }
                else if(timer.elapsedTime() >= miningTime-(miningTime/4)){
                    miningLevel = 3;
                }
                else if(timer.elapsedTime() >= miningTime/2){
                    miningLevel = 2;
                } else if(timer.elapsedTime() >= miningTime/4){
                    miningLevel = 1;
                }
            }
        }
    }else if(mining){
        std::cout << "you moved" << std::endl;
        this->stopMining();
    }
}

void Player::stopMining(){
    mining = false;
    miningLevel = 0;
    timer.reset();
}

void Player::render(){
    SpriteHandler::getInstance()->get(SPRITE_CODE::player)->draw(this->getPosition());
    if(mining){
        switch(miningLevel){
        case 1:
            SpriteHandler::getInstance()->get(destruction1)->draw(miningX, miningY, SPRITE_SIZE, SPRITE_SIZE);
            break;
        case 2:
            SpriteHandler::getInstance()->get(destruction2)->draw(miningX, miningY, SPRITE_SIZE, SPRITE_SIZE);
            break;
            case 3:
                SpriteHandler::getInstance()->get(destruction3)->draw(miningX, miningY, SPRITE_SIZE, SPRITE_SIZE);

                break;
                
            
        }
    }
}