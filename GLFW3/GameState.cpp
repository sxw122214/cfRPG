//
//  GameState.cpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "GameState.hpp"

GameState::GameState(){

}

void GameState::setup(){
    //load world and sprites at the same time
    int worldSave;
    std::cout << "What world number would you like to load?" << std::endl << "A default world will be loaded if it can't be found" << std::endl;
    std::cin >> worldSave;
    std::thread worldT(&WorldHandler::loadWorld, WorldHandler::getInstance(), worldSave);
    SpriteHandler::getInstance()->loadImages();
    worldT.join();
    
    player.loadPlayerData(worldSave);
    
    worldHandler = WorldHandler::getInstance();
    
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
}

void GameState::keyPressed(int key){
    if(key == 84){
        saveWorld();
    }
}

void GameState::pushBothRU(GameObject *go){
    renderVector.push_back(go);
    updateVector.push_back(go);
}

void GameState::saveWorld(){
    std::thread playerSave(&Player::savePlayerData, player, worldHandler->getWorldIntLoaded());
    std::ofstream myfile;
    myfile.open ("data/world"+std::to_string(worldHandler->getWorldIntLoaded())+".csv");
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
}