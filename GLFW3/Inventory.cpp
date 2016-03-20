
//
//  Inventory.cpp
//  Project2
//
//  Created by William Meaton on 12/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Inventory.hpp"


void Inventory::pickup(Item* item, int amount){
    for(auto &i : held){
        if(i.type==item && i.num+1 <= maxStackSize){
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

int Inventory::size(){
    return held.size();
}

int Inventory::getSelectedPos(){
    return selected;
}

bool Inventory::isEmpty(){
    return this->size() == 0;
}