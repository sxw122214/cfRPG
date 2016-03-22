//
//  Inventory.cpp
//  Project2
//
//  Created by William Meaton on 12/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Inventory.hpp"


void Inventory::pickup(Item* item, int amount){
    
    //
//    if(getSelected()->type == item){
//        if(getSelected()->num+amount > maxStackSize){
//            getSelected()->num = maxStackSize;
//            amount = (getSelected()->num+amount) - maxStackSize;
//        }else{
//            getSelected()->num+=amount;
//            return;
//        }
//    }
    for(auto &i : held){
        if(i.type==item){
            if(i.num+amount > maxStackSize){
                i.num = maxStackSize;
                amount = (i.num+amount)-maxStackSize;
                continue;
            }
            i.num+=amount;
            return;
        }
    }
    held.push_back(inventoryItem(item, amount));
}

bool Inventory::backwards(){
    if(selected-1 < 0){
        selected = 0;
    }else{
        selected--;
    }
    if(!isEmpty()){
        //if it's not empty it means it moved the selected poiinter
        return true;
    }
    return false;
}

bool Inventory::forwards(){
    if(selected+1 >= size()){
        selected = 0;
    }else{
        selected++;
    }
    if(!isEmpty()){
        //if it's not empty it means it moved the selected pointer
        return true;
    }
    return false;
}

void Inventory::clear(){
    held.clear();
    selected = 0;
}

bool Inventory::reduceSelected(){
    held[selected].num--;
    //if there's none there
    if(held[selected].num <= 0){
        held.erase(held.begin()+selected);
        //set the inventorySelected to the next one, or the one before or just 0
        if(selected+1 >= size()){
            if(selected-1 < 0){
                selected = 0;
            }else{
                selected--;
                return true;
            }
        }else{
            selected++;
            return true;
        }
    }
    return false;
}

Inventory::inventoryItem* Inventory::getSlot(int i){
    if(i >= 0 && i < size()){
        return &held[i];
    }
    return nullptr;
}

Inventory::inventoryItem* Inventory::getSelected(){
    if(selected >= 0 && selected < size()){
        return &held[selected];
    }
    return nullptr;
}

void Inventory::display(Graphics::Text* text){
    glPushMatrix();
    //move it over a little, pushpop because easy
    glTranslatef(30, 30, 0);
    //colour it nicely
    glColor4d(0.8, 0.8, 0.8, 0.1);
    //draw a rectangle as a backround
    Graphics::drawRect(0, 0, 5*SPRITE_SIZE+24, 5*SPRITE_SIZE+24);
    
    int j = 0;
    //loop through it and show it
    for(int i = 0; i < held.size(); i++){
        if(selected == i){
            glColor3d(0, 0, 0);
            Graphics::drawRect((i%5)*SPRITE_SIZE+((i%5+1)*2), (j)*SPRITE_SIZE+((j+1)*2), SPRITE_SIZE+4, SPRITE_SIZE+4);
        }
        glColor4d(1, 1, 1, 1);
        //show the item
        SpriteHandler::getInstance()->get(held[i].type->textureCode)->draw((i%5)*SPRITE_SIZE+((i%5+1)*4), (j)*SPRITE_SIZE+((j+1)*4), SPRITE_SIZE, SPRITE_SIZE);
        glColor4d(1, 1, 1, 1);
        //show the amount
        text->draw(std::to_string(held[i].num), (i%5)*SPRITE_SIZE+((i%5+1)*4), (j+1)*(SPRITE_SIZE)+((j+1)*2));//+((j+1)*4));
        if(i%4==0 && i!=0){
            j++;
        }
    }
    glPopMatrix();
    glColor4d(1, 1, 1, 1);
}

int Inventory::size(){
    return (int)held.size();
}

int Inventory::getSelectedPos(){
    return selected;
}

bool Inventory::isEmpty(){
    return this->size() == 0;
}