//
//  Player.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <algorithm>
#include "Creature.hpp"
#include "Handlers.h"
#include "Tile.hpp"
#include "Timer.hpp"
#include "Item.hpp"

class Player : public GameObject{
public:
    Player(const Math::Vector2D &scene, const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible);
    virtual void render();
    virtual void update();
    float speed = 8;
    std::shared_ptr<WorldHandler>  worldHandler;
    std::shared_ptr<InputHandler> inputHandler;
    
    class inventoryItem{
    public:
        inventoryItem(Item* type, int num){
            this->type = type;
            this->num = num;
        }
        Item* type;
        int num;
    };

    //collection and mining stuff
    void stopMining();
    void pickup(Item*);
    void placeItem();
    bool mining = false;
    float miningTime = 0;
    int miningX = 0, miningY = 0;
    int miningType = 0, miningLevel = 0;
    int inventorySelected = 0;
    Math::Timer timer;
    std::vector<inventoryItem> inventory;
};

#endif /* Player_hpp */
