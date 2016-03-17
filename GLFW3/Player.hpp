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
#include "Inventory.hpp"
#include <dT/drawtext.h>

class Player : public GameObject{
public:
    //constructor, goes to GO
    Player(const Math::Vector2D &scene, const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible);
    //render that's called every frame
    virtual void render();
    //draws the animation if you're mining a tile
    void miningAnimation();
    //renders the inventory above the player
    void renderInventory();
    //update that's called every frame
    virtual void update();
    
    void loadPlayerData(int num);
    void savePlayerData(int num);
    
    //the players speed
    float speed = 5;
    //pointers to handlers
    std::shared_ptr<WorldHandler>  worldHandler;
    std::shared_ptr<InputHandler> inputHandler;
    
    //loaded font, not used currently
    struct dtx_font *font;
    
    //
    //collection and mining stuff
    //
    
    //Stops mining, resets the clocks etc
    void stopMining();
    //holds whether you're mining or not
    bool mining = false;
    //used to decide when to draw the inventory, reset by changing your selection
    float inventoryItemDisplayAlpha = 0;
    //the mining time of the current tile
    float miningTime = 0;
    //the current interacted tile
    int selectedX = 0, selectedY = 0;
    //holds how far along you are mining a tile, used to show the animations
    int miningLevel = 0;
    //the mining timer
    Math::Timer timer;
    //the inventory
    Inventory inv;
};

#endif /* Player_hpp */
