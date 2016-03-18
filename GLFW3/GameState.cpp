//
//  GameState.cpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState(){
    text.loadGlyphmap(20);
    worldHandler = WorldHandler::getInstance();
}

void GameState::setup(){
    
}

void GameState::exitCalled(){
    //save the world
    saveWorld();
    //reset the world data
    worldHandler->resetData();
    //clear the vectors of update and render
    updateVector.clear();
    renderVector.clear();
    //reset the player data
    player.resetPlayerData();
    //also reset the world saving stuff
    savedAlpha = 0;
    //set the new state!
    State::setState(STATES::menu);

}

void GameState::loadWorld(int world){
    worldLoaded = world;
    //load world and sprites at the same time
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), worldLoaded);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
    //load the player inventory and position
    player.loadPlayerData(worldLoaded);
    //add the player to the render and update loop
    pushBothRU(&player);
}


void GameState::update(){
    for(auto go : updateVector){
        go->update();
    }
}

void GameState::draw(){
    worldHandler->renderWorld();
    for(auto go : renderVector){
        if(go->isVisible()){
            if(worldHandler->getOffSetX() == go->getScene().x && worldHandler->getOffSetY() == go->getScene().y){
                go->render();
            }
        }
    }
    //if the world has recently been saved, show an indicator
    if(savedAlpha > 0){
        glColor4f(0, 0, 0, savedAlpha);
        text.draw("World saved...", 60, 60);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        savedAlpha -= 0.005;
    }
}

void GameState::keyPressed(int key){
    //if T is pressed
    if(key == 84){
        saveWorld();
    }
}

void GameState::pushBothRU(GameObject *go){
    renderVector.push_back(go);
    updateVector.push_back(go);
}

void GameState::saveWorld(){
    //start the playerSave thread
    std::thread playerSave(&Player::savePlayerData, player, worldLoaded);
    std::ofstream myfile;
    //save the worldfile
    myfile.open ("data/world"+std::to_string(worldLoaded)+".csv");
    for(int i = 0; i < worldHandler->getMap().size(); i++){
        myfile << worldHandler->getMap()[i]->id;
        if(i%worldHandler->getxMapSize() == 0 && i !=0){
            myfile << std::endl;
        }else{
            myfile << ",";
        }
    }
    std::cout << "file saved" << std::endl;
    myfile.close();
    playerSave.join();
    //set the alpha so that the text appears
    savedAlpha = 1;
}