//
//  MapCreationState.cpp
//  Project2
//
//  Created by William Meaton on 28/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "MapCreationState.hpp"

MapCreationState::MapCreationState(){
    iH = InputHandler::getInstance();
    wH = WorldHandler::getInstance();
    text.loadGlyphmap(20);
}

MapCreationState::~MapCreationState(){
}

void MapCreationState::loadWorld(int world){
    worldLoaded = world;
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), worldLoaded);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
}

void MapCreationState::update(){
    wH->updateWorld();
    if(iH->getMOUSE0()){
        int x = iH->getMouseX();
        int y = iH->getMouseY();
        x = int(x/SPRITE_SIZE);
        y = int(y/SPRITE_SIZE);
        std::cout << x << " " << y << std::endl;
        x += ((wH->windowWidth/SPRITE_CODE::SPRITE_SIZE)*wH->getOffSetX());
        y += ((wH->windowHeight/SPRITE_CODE::SPRITE_SIZE)*wH->getOffSetY());
        std::cout << x << " " << y << std::endl;
        wH->getMap()[x+(y*wH->getxMapSize())] = &wH->getTiles()[currentTexture];
    }
}

void MapCreationState::draw(){
    wH->renderWorld();
    SpriteHandler::getInstance()->get(currentTexture)->draw(iH->getMouseX(), iH->getMouseY(), SPRITE_SIZE, SPRITE_SIZE);
    //if the world has recently been saved, show an indicator
    if(savedAlpha > 0){
        glColor4f(0, 0, 0, savedAlpha);
        text.draw("World saved...", 60, 60);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        savedAlpha -= 0.005;
    }
}

void MapCreationState::keyPressed(int key){
    if(key == 80){
        std::cout << "right" << std::endl;
        if(currentTexture < SPRITE_CODE::END_SPRITE){
            currentTexture++;
        }else{
            currentTexture = 0;
        }
    }
    if(iH->getRIGHT()){
        wH->offSetby(1, 0, true);
    }
    if(iH->getLEFT()){
        wH->offSetby(-1, 0, true);
    }
    if(iH->getDOWN()){
        wH->offSetby(0, 1, true);
    }
    if(iH->getUP()){
        wH->offSetby(0, -1, true);
    }
    if(key == 84){
        saveMap();
    }
}

void MapCreationState::saveMap(){
    std::ofstream myfile;
    myfile.open("data/saves/world"+std::to_string(worldLoaded)+".csv");
    for(int i = 0; i < wH->getMap().size(); i++){
        myfile << wH->getMap()[i]->id;
        if(i%wH->getxMapSize() == 0 && i !=0){
            myfile << std::endl;
        }else{
            myfile << ",";
        }
    }
    std::cout << "file saved" << std::endl;
    myfile.close();
    savedAlpha = 1;
}