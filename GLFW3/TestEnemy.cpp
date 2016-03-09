//
//  TestEnemy.cpp
//  Project2
//
//  Created by William Meaton on 07/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "TestEnemy.hpp"

TestEnemy::TestEnemy(const Math::Vector2D &position, const Math::Vector2D &scene, const Graphics::Rect &bounds, bool visible, float health) : NPC(position, scene, bounds, visible, health){
    
}

void TestEnemy::update(){
    Math::Vector2D sv(1, 1);
    WorldHandler::getInstance()->movementCheck(editPosition(), sv, editScene(), true, false);
}

void TestEnemy::render(){
    SpriteHandler::getInstance()->get(SPRITE_CODE::S_player)->draw(this->getPosition());
}

void TestEnemy::talk(GameObject *go){
    Math::Vector2D thisV = this->getPosition();
    Math::Vector2D thisS = this->getScene();
    Math::Vector2D goV = go->getPosition();
    Math::Vector2D goS = go->getScene();
    thisV += thisV*thisS;
    goV += goV*goS;
    if(Math::absolute(Math::vectorDistance(thisV, goV)) < 100){
        std::cout << "Hellow there stranger" << std::endl;
    }
}