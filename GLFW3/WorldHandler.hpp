//
//  WorldHandler.hpp
//  Project2
//
//  Created by William Meaton on 20/01/2016.
//
//

#ifndef WorldHandler_hpp
#define WorldHandler_hpp

#include <stdio.h>
#include <vector>
#include "coreMain.h"
#include <memory>
#include <fstream>
#include "SpriteHandler.hpp"
#include "Tile.hpp"
#include "Item.hpp"
#include "InputHandler.hpp"

class WorldHandler{
public:
    WorldHandler(){}; //no creation needed
    //returns the instance of the handler
    static std::shared_ptr<WorldHandler> getInstance();
    
    //reset the
    void resetData();
    
    //loads a specific world from a csv file
    void loadWorld(int i);
    
    //renders and updates the world
    void renderWorld();
    void updateWorld();
    
    //manages offsets in rendering
    bool offSetby(int x, int y, bool set);
    bool offSetby(const Math::Vector2D &v, bool set);
    int getOffSetX();
    int getOffSetY();
    
    //does world collision and corrects on the xandY axis
    bool worldCollideY(Math::Vector2D &position, Math::Vector2D &scene, float &v);
    bool worldCollideX(Math::Vector2D &position, Math::Vector2D &scene, float &v);

    bool belowWorldCollide(Math::Vector2D &position, Math::Vector2D &scene);
    
    //all objects that move must go through this method, it contains collisions and scene changing
    void movementCheck(Math::Vector2D &current, Math::Vector2D &velocity, Math::Vector2D &scene, bool allowedOffscreen, bool moveScene);
    
    //loads the tile types, will be called if not called before loadWorld is called
    void loadTileTypes();
    void loadItemTypes();
    
    //returns if things are loaded
    bool isWorldLoaded();
    bool isTypesLoaded();
    bool isItemsLoaded();
    
    //returns the map, tiles and items
    std::vector<Tile*>& getMap();
    std::vector<Tile>& getTiles();
    std::vector<Item*>& getItems();
    
    //returns a pointer reference
    Tile*& getTile(int x, int y);
    
    //returns the X and Y size of the map in tiles
    int getxMapSize();
    int getyMapSize();
    
    int windowWidth, windowHeight;
    ~WorldHandler();
private:
    //creation and singleton method blocks
    WorldHandler(WorldHandler const &s){}; // no copy constructor
    WorldHandler& operator=(WorldHandler const &s){ return *this;}; //no assignment
    //the only instance allowed
    static std::shared_ptr<WorldHandler> instance;
        
    //initial offset
    int offSetX = 0, offSetY = 0;
        
    //if the world/tiles are loaded
    bool worldLoaded = false, typeLoaded = false, itemLoaded = false;
    
    //map holds pointers to tiles in the tiles vector
    std::vector<Tile*> map;
    //tiles holds the initial information of each tile
    std::vector<Tile> tiles;
    //Items holds the information all the items
    std::vector<Item*> items;
    
    //this holds how big the map is in tiles
    int xMapSize = 0, yMapSize = 0;
};

#endif /* WorldHandler_hpp */
