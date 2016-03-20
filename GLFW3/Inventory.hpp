//
//  Inventory.hpp
//  Project2
//
//  Created by William Meaton on 12/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp

#include <stdio.h>
#include "Item.hpp"
#include <vector>

class Inventory{
    class inventoryItem{
    public:
        inventoryItem(Item* type, int num){
            this->type = type;
            this->num = num;
        }
        Item* type;
        int num;
    };
    int maxStackSize = 64;
    int selected = 0;
    std::vector<inventoryItem> held;
public:
    Inventory(){};
    
    //returns the size of the inventory
    int size();
    
    //wipes the memory
    void clear();
    
    //gets the current selected int
    int getSelectedPos();
    
    //returns if the inventory is empty
    bool isEmpty();
    
    //pickups an item and pushes it back into held
    void pickup(Item*, int amount);
    
    //returns true if selected item is changed
    bool forwards();
    bool backwards();
    
    //returns true if the item reduced is removed
    bool reduceSelected();
    
    //returns the currently selected item
    inventoryItem* getSelected();
    
    //returns the item at a point
    inventoryItem* getSlot(int i);
};

#endif /* Inventory_hpp */
