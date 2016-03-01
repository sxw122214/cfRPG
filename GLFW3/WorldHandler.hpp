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
#include "InputHandler.hpp"
#include "GameObject.hpp"

class WorldHandler{
public:
    //public class tile, one is loaded for each type of tile in the world
    class Tile{
    public:
        Tile(int tc, bool solid){
            this->textureCode = tc;
            this->solid = solid;
        }
        Tile(int tc){
            this->textureCode = tc;
        }
        int textureCode;
        bool solid = false;
    };
    
    WorldHandler(){}; //no creation needed
    //returns the instance of the handler
    static std::shared_ptr<WorldHandler> getInstance();
    
    //loads a specific world from a csv file
    void loadWorld(int i);
    
    //renders and updates objects in the world
    void renderWorld();
    void updateWorld();
    
    //manages offsets in rendering
    bool offSetby(int x, int y, bool set);
    bool offSetby(const Math::Vector2D &v, bool set);
    int getOffSetX();
    int getOffSetY();
    
    bool worldCollide(Math::Vector2D &position, Math::Vector2D &scene, Math::Vector2D &v);
    
    //all objects that move must go through this method, it contains collisions and scene changing
    void movementCheck(Math::Vector2D &current, Math::Vector2D &velocity, Math::Vector2D &scene, bool allowedOffscreen, bool moveScene);
    
    void addToRQueue(GameObject*);
    void addToUQueue(GameObject*);
    void addToQueues(GameObject*);
    
    //loads the tile types, will be called if not called before loadWorld is called
    void loadTileTypes(int typeNum);
    
    //returns if things are loaded
    bool isWorldLoaded();
    bool isTypesLoaded();
    
    std::vector<Tile*>& getMap();
    std::vector<Tile>& getTiles();
    
    int getxMapSize();
    int getyMapSize();
    
    int windowWidth, windowHeight;
    ~WorldHandler();
private:
    //creation and singleton method blocks
    WorldHandler(WorldHandler const &s){}; // no copy constructor
    //WorldHandler& operator=(WorldHandler const &s){}; //no assignment
    //the only instance allowed
    static std::shared_ptr<WorldHandler> instance;
    
    //initial offset
    int offSetX = 0, offSetY = 0;
    
    //if the world/tiles are loaded
    bool worldLoaded = false, typeLoaded = false;
    
    //objects
    std::vector<GameObject*> renderVector;
    std::vector<GameObject*> updateVector;
    
    //map holds pointers to tiles in the tiles vector
    std::vector<Tile*> map;
    //tiles holds the initial information of each tile
    std::vector<Tile> tiles;
    
    //this holds how big the map is in tiles
    int xMapSize = 0, yMapSize = 0;

};

#endif /* WorldHandler_hpp */
