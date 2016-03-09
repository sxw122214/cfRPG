//
//  GameObject.cpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#include "GameObject.hpp"


GameObject::GameObject(const Math::Vector2D &position, const Math::Vector2D &scene,  const Graphics::Rect &bounds, bool visible): visible(visible), bounds(bounds), position(position), scene(scene){
}

const bool& GameObject::isVisible(){
    return visible;
}

const Math::Vector2D& GameObject::getPosition(){
    return position;
}

Math::Vector2D& GameObject::editPosition(){
    return position;
}

const Math::Vector2D& GameObject::getScene(){
    return scene;
}

Math::Vector2D& GameObject::editScene(){
    return scene;
}

void GameObject::setPosition(const Math::Vector2D &v){
    this->position = v;
}

void GameObject::setPosition(const float &x, const float &y){
    this->position.x = x;
    this->position.y = y;
}

void GameObject::setScene(const Math::Vector2D &v){
    this->scene = v;
}

void GameObject::setScene(const float &x, const float &y){
    this->scene.x = x;
    this->scene.y = y;
}

void GameObject::gravity(bool collision){
    if(collision){
        Math::Vector2D v(0, gravityStrength);
        WorldHandler::getInstance()->movementCheck(position, v, scene, true, true);
    }else{
        this->position.y += gravityStrength;
    }
}
