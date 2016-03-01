//
//  SpriteHandler.cpp
//  Project2
//
//  Created by William Meaton on 20/01/2016.
//
//

#include "SpriteHandler.hpp"

std::shared_ptr<SpriteHandler> SpriteHandler::instance;

std::shared_ptr<SpriteHandler> SpriteHandler::getInstance(){
    if(!instance){
        instance = std::make_shared<SpriteHandler>();
    }
    return instance;
}

void SpriteHandler::loadImages(){
    //load the images and confirm if they are or not
    for(int i = 0; i < SPRITE_CODE::END_SPRITE; i++){
        Graphics::Image* temp = new Graphics::Image;
        
        if(temp->loadImage("S_"+std::to_string(i)+".png")){
            images[i].reset(temp);
            std::cout << "Image Loaded " << i << std::endl;
        }else{
            std::cout << "Image failed to load " << i << std::endl;
        }
    }
}

std::unique_ptr<Graphics::Image>& SpriteHandler::get(int i){
    if(i < SPRITE_CODE::END_SPRITE && i >= 0){
        return images[i];
    }
    return images[0];
}