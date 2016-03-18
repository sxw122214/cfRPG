 //
//  WorldHandler.cpp
//  Project2
//
//  Created by William Meaton on 20/01/2016.
//
//

#include "WorldHandler.hpp"

std::shared_ptr<WorldHandler> WorldHandler::instance;

WorldHandler::~WorldHandler(){
    
}

std::shared_ptr<WorldHandler> WorldHandler::getInstance(){
    if(!instance){
        instance = std::make_shared<WorldHandler>();
    }
    return instance;
}


void WorldHandler::movementCheck(Math::Vector2D &current, Math::Vector2D &velocity, Math::Vector2D &scene, bool allowedOffscreen, bool moveScene){
    bool yCollide = true, xCollide = true;
    //if there's collision with world, given the current position, scene and velocity
    if(!worldCollideY(current, scene, velocity.y)){
        current.y += velocity.y;
        yCollide = false;
    }
    
    if(!worldCollideX(current, scene, velocity.x)){
        current.x += velocity.x;
        xCollide = false;
    }
    
    if(yCollide && xCollide){
        return;
    }
    
    //if it's not allowed off screen, just stop here
    //things will still move off screen though
    if(!allowedOffscreen){
        return;
    }
    
    //UP
    if(current.y+SPRITE_SIZE > this->windowHeight){
        //check ther is a scene ontop
        if(offSetby(0, 1, moveScene)){
            //adjust the y to the top of the next scene
            current.y = 0;
            //change the scene so it's rendered
            scene.y += 1;
        }else{
            //if not do box collision
            current.y = windowHeight-SPRITE_SIZE;
        }
    }
    
    //DOWN
    if(current.y < 0){
        //check if there is anything below
        if(offSetby(0, -1, moveScene)){
            //change y to the bottom of next scene
            current.y = windowHeight-SPRITE_SIZE;
            //adjust scene
            //1 is technically up
            scene.y += -1;
        }else{
            //else correct the collision
            current.y = 0;
        }
    }
    
    //LEFT
    if(current.x < 0){
        //check if there is a scene to the left
        if(offSetby(-1, 0, moveScene)){
            //set the x to the far left of the next scene
            current.x = windowWidth-SPRITE_SIZE;
            //adjust the scene
            scene.x += -1;
        }else{
            current.x = 0;
        }
    }
    
    //RIGHT
    if(current.x+SPRITE_SIZE > windowWidth){
        //check if there is a scene to the rihgt
        if(offSetby(1, 0, moveScene)){
            //adjust values
            current.x = 0;
            scene.x += 1;
        }else{
            //correct collision
            current.x = windowWidth-SPRITE_SIZE;
        }
    }

}

bool WorldHandler::offSetby(int x, int y, bool set){
    //if it's less than the size of the map
    if(offSetX+x < 0 || offSetY+y < 0){
        return false;
    }
    //if it's bigger than the size of the map
    if(offSetX+x >= xMapSize/(windowWidth/SPRITE_CODE::SPRITE_SIZE) ||
       offSetY+y >= yMapSize/(windowHeight/SPRITE_CODE::SPRITE_SIZE)){
        return false;
    }
    if(set){
        this->offSetX += x;
        this->offSetY += y;
    }
    return true;
}

bool WorldHandler::offSetby(const Math::Vector2D &v, bool set){
    return this->offSetby(v.x, v.y, set);
}

bool WorldHandler::belowWorldCollide(Math::Vector2D &position, Math::Vector2D &scene){
    Math::Vector2D temp(0, 2);
    return worldCollideY(position, scene, temp.y);
}

bool WorldHandler::worldCollideX(Math::Vector2D &position, Math::Vector2D &scene, float &v){
    float xCheck;
    bool right = false, left = false;
    if(v > 0){
        right = true;
        xCheck = position.x + v + SPRITE_SIZE;
    }else if(v < 0){
        //if it's going left
        left = true;
        xCheck = position.x - v;
    }else if (v == 0){
        //if x is 0, thus no x movement
        xCheck = position.x + SPRITE_SIZE/2;
    }
    Math::Vector2D gridPosition = Math::Vector2D((int)xCheck/SPRITE_SIZE, (int)(position.y+SPRITE_SIZE/2)/SPRITE_SIZE);
    Math::Vector2D mapPosition(gridPosition.x + scene.x*(windowWidth/SPRITE_SIZE), gridPosition.y + scene.y*(windowHeight/SPRITE_SIZE));
    //if it's going off the map
    if(mapPosition.x < 0 || mapPosition.y < 0 || mapPosition.x > xMapSize || mapPosition.y > xMapSize){
        return true;
    }
    
    if(map[mapPosition.x + mapPosition.y*xMapSize]->solid){
        if(right){
            //going right
            position.x = (gridPosition.x-1)*SPRITE_SIZE;
        }else{
            //going left
            position.x = (gridPosition.x+1)*SPRITE_SIZE;
        }
        return true;
    }
    return false;
}

bool WorldHandler::worldCollideY(Math::Vector2D &position, Math::Vector2D &scene, float &v){
    float yCheck;
    bool up = false, down = false;
    if(v > 0){
        //if it's going down
        down = true;
        yCheck = position.y + v + SPRITE_SIZE;
    }else if (v < 0){
        //if it's going up
        up = true;
        yCheck = position.y - v;
    } else if (v == 0){
        //if y is 0, thus no y movement
        yCheck = position.y + SPRITE_SIZE/2;
    }
    Math::Vector2D gridPosition = Math::Vector2D((int)(position.x+SPRITE_SIZE/2)/SPRITE_SIZE, (int)yCheck/SPRITE_SIZE);
    Math::Vector2D mapPosition(gridPosition.x + scene.x*(windowWidth/SPRITE_SIZE), gridPosition.y + scene.y*(windowHeight/SPRITE_SIZE));
    
    //if it's going off the map
    if(mapPosition.x < 0 || mapPosition.y < 0 || mapPosition.x > xMapSize || mapPosition.y > xMapSize){
        return true;
    }
    if(map[mapPosition.x + mapPosition.y*xMapSize]->solid){
        if(up){
            position.y = (gridPosition.y+1)*SPRITE_SIZE;
            v = 0;
        }else{
            position.y = (gridPosition.y-1)*SPRITE_SIZE;
        }
        return true;
    }
    return false;
}

void WorldHandler::loadTileTypes(){
    const char seperator = ',';
    std::ifstream worldFile("data/tiles.csv", std::ios::in); //declare a file stream
    if (worldFile.is_open()) //checks if the file is open??
    {
        std::string str;
        while (getline(worldFile, str)){
            //if it's a / just ignore the entire line
            if(str[0] == '/'){
                continue;
            }
            
            //loop through and push all the tiles into a vector
            std::vector<int> readIntegers; // this will hold the data
            std::string read;
            for(int i = 0; i <= str.length(); i++){
                //find seperators and split the integers
                //this allows for >1 digit ints
                // i >= str.length finds the end of the line
                if(str[i] == seperator || i >= str.length()){
                    int tempInt = atoi(read.c_str());
                    read.clear();
                    readIntegers.push_back(tempInt);
                }else{
                    read += str[i];
                }
            }
            //now push the integers in
            tiles.push_back(Tile(readIntegers[0], readIntegers[1], readIntegers[2], readIntegers[3], readIntegers[4]));
        }
        typeLoaded = true;
        std::cout << "Tiles loaded" << std::endl;
    }else{
        typeLoaded = false;
        std::cout << "Tile file failed to load" << std::endl;
    }
}

void WorldHandler::loadItemTypes(){
    const char seperator = ',';
    std::ifstream worldFile("data/items.csv", std::ios::in); //declare a file stream
    if (worldFile.is_open()) //checks if the file is open??
    {
        std::string str;
        while (getline(worldFile, str)){
            //if it's a / just ignore the entire line
            if(str[0] == '/'){
                continue;
            }
            
            //loop through and push all the tiles into a vector
            std::vector<int> readIntegers; // this will hold the data
            std::string read;
            for(int i = 0; i <= str.length(); i++){
                //find seperators and split the integers
                //this allows for >1 digit ints
                // i >= str.length finds the end of the line
                if(str[i] == seperator || i >= str.length()){
                    int tempInt = atoi(read.c_str());
                    read.clear();
                    readIntegers.push_back(tempInt);
                }else{
                    read += str[i];
                }
            }
            //now push the integers in
            items.push_back(new Item(readIntegers[0], readIntegers[1], readIntegers[2], readIntegers[3]));
        }
        typeLoaded = true;
        std::cout << "Items loaded" << std::endl;
    }else{
        typeLoaded = false;
        std::cout << "Item file failed to load" << std::endl;
    }
}


void WorldHandler::loadWorld(int worldNum){
    if(!typeLoaded){
        this->loadTileTypes();
    }
    if(!itemLoaded){
        this->loadItemTypes();
    }
    const char seperator = ',';
    std::ifstream worldFile("data/world"+std::to_string(worldNum)+".csv", std::ios::in); //declare a file stream
    if (!worldFile.is_open()) //checks if the file is open, if not load a template
    {
        std::cout << "World file not found, loading a template" << std::endl;
        worldFile = std::ifstream("data/templateWorld.csv", std::ios::in); //declare a new file stream of the template world
    }
        std::string str;
        while (getline(worldFile, str)){
            //loop through and push all the ints to a vector
            std::string read;
            for(int i = 0; i <= str.length(); i++){
                //find seperators and split the integers
                //this allows for >1 digit ints
                // i >= str.length finds the end of the line
                if(str[i] == seperator || i >= str.length()){
                    xMapSize++;
                    int tempInt = atoi(read.c_str()); // turn into an int
                    read.clear(); // clear the read String for next time
                    //if the tempInt is incorrect or invalid
                    if(tempInt > tiles.size() || tempInt < 0){
                        std::cout << "World failed to load, invalid tile ID";
                        return;
                    }
                    map.push_back(&tiles[tempInt]);
                }else{
                    read += str[i];
                }
            }
            //count how many lines there are
            yMapSize++;
        }
        //xMapSize will end up being xSize*number of lines
        //so fix that
        xMapSize = xMapSize/yMapSize;
        worldLoaded = true;
    std::cout << "World loaded" << std::endl;
}

void WorldHandler::updateWorld(){
}


void WorldHandler::renderWorld(){
    //don't draw if it's not been loaded
    if(!worldLoaded){
        std::cout << "No world loaded" << std::endl;
        return;
    }
    auto temp = SpriteHandler::getInstance();
    //it needs to be abs'd but not the actual value
    int tempOffSetX = Math::absolute(offSetX);
    int tempOffSetY = Math::absolute(offSetY);
    
    //the min and  max offsets are so it only renders the curreent scene
    //this cuts CPU and GPU strain by a crazy amount
    int minOffSetX = tempOffSetX*(windowWidth/SPRITE_CODE::SPRITE_SIZE);
    int minOffSetY = tempOffSetY*(windowHeight/SPRITE_CODE::SPRITE_SIZE);
    
    //needs +1 to correct the mathematics
    int maxOffSetX = (tempOffSetX+1)*(windowWidth/SPRITE_CODE::SPRITE_SIZE);
    int maxOffSetY = (tempOffSetY+1)*(windowHeight/SPRITE_CODE::SPRITE_SIZE);
    
    //check if they're trying to load out of bounds
    if(maxOffSetY > yMapSize || maxOffSetX > xMapSize){
        std::cout << "Map coords out of bounds" << std::endl;
        return;
    }
    //draw the world using the offsets
    for(int i = minOffSetY; i < maxOffSetY; i++){
        for(int j = minOffSetX; j < maxOffSetX; j++){
            //draw the sprites
            temp->get(map[j+i*xMapSize]->textureCode)->draw(((j-minOffSetX)*SPRITE_CODE::SPRITE_SIZE), ((i-minOffSetY)*SPRITE_CODE::SPRITE_SIZE), SPRITE_CODE::SPRITE_SIZE, SPRITE_CODE::SPRITE_SIZE);
        }
    }
}

std::vector<Tile*>& WorldHandler::getMap(){
    return map;
}

std::vector<Tile>& WorldHandler::getTiles(){
    return tiles;
}

std::vector<Item*>& WorldHandler::getItems(){
    return items;
}

Tile*& WorldHandler::getTile(int x, int y){
    x = int(x/SPRITE_SIZE);
    y = int(y/SPRITE_SIZE);
    x += (windowWidth/SPRITE_SIZE)*getOffSetX();
    y += (windowHeight/SPRITE_SIZE)*getOffSetY();
    return map[x+(y*getxMapSize())];
}

int WorldHandler::getxMapSize(){
    return xMapSize;
}

int WorldHandler::getyMapSize(){
    return yMapSize;
}

int WorldHandler::getOffSetX(){
    return offSetX;
}

int WorldHandler::getOffSetY(){
    return offSetY;
}

bool WorldHandler::isWorldLoaded(){
    return worldLoaded;
}

bool WorldHandler::isTypesLoaded(){
    return typeLoaded;
}

bool WorldHandler::isItemsLoaded(){
    return itemLoaded;
}