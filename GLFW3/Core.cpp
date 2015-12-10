//
//  Core.cpp
//  GLFW3
//
//  Created by William Meaton on 08/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#include "Core.hpp"

void Core::setup(){
    img.loadImage("/Users/williammeaton/Desktop/GLFW3/img.jpg", 433, 512);
}

void Core::update(){
    
}

void Core::draw(){
    using namespace Graphics;
    img.draw(0, 0);
}

void Core::keyPressed(int key){

}

void Core::keyReleased(int key){
    
}