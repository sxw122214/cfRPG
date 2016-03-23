//
//  Player.cpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#include "Player.hpp"

Player::Player(const Math::Vector2D &scene, const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible): GameObject(scene, position, bounds, visible){
    worldHandler = WorldHandler::getInstance();
    inputHandler = InputHandler::getInstance();
    text.loadGlyphmap(18);
}

void Player::resetPlayerData(){
    //clear the inventory
    inv.clear();
}

void Player::loadPlayerData(int num){
    const char seperator = ',';
    std::ifstream worldFile("data/saves/player"+std::to_string(num)+".csv", std::ios::in); //declare a file stream
    if (worldFile.is_open()) //checks if the file is open??
    {
        std::string str;
        int linenumber = 0;
        while (getline(worldFile, str)){
            //if it's a / just ignore the entire line
            if(str[0] == '/'){
                continue;
            }
            //loop through and do appropriate things with the data
            std::vector<int> readIntegers; // this will hold the data
            std::string read;
            for(int i = 0; i <= str.length(); i++){
                if(str[i] == seperator || i >= str.length()){
                    int tempInt = atoi(read.c_str());
                    read.clear();
                    readIntegers.push_back(tempInt);
                }else{
                    read += str[i];
                }
            }
            linenumber++;
            if(linenumber == 1){
                editPosition().x = readIntegers[0];
                editPosition().y = readIntegers[1];
            }else if(linenumber == 2){
                editScene().x = readIntegers[0];
                editScene().y = readIntegers[1];
            }else if(linenumber >2){
                inv.pickup(worldHandler->getItems()[readIntegers[0]], readIntegers[1]);
            }
            
        }
        std::cout << "Player data loaded" << std::endl;
    }else{
        std::cout << "No player data found, using blank" << std::endl;
    }
    //offset the world
    worldHandler->offSetby(getScene().x, getScene().y, true);
}

void Player::savePlayerData(int num){
    std::ofstream myfile;
    myfile.open ("data/saves/player"+std::to_string(num)+".csv");
    //save the position
    myfile << int(getPosition().x) << "," << int(getPosition().y) << std::endl;
    //save the scene
    myfile << getScene().x << "," << getScene().y << std::endl;
    //save the inventory
    for(int i = 0; i < inv.size(); i++){
        myfile << inv.getSlot(i)->type->id << "," << inv.getSlot(i)->num << std::endl;
    }
    std::cout << "player saved" << std::endl;
    myfile.close();

}

void Player::update(){
    int thisMouseX = inputHandler->getMouseX();
    int thisMouseY = inputHandler->getMouseY();
    bool movement = false;
    this->isTouchingBelow = WorldHandler::getInstance()->belowWorldCollide(editPosition(), editScene());
    this->gravity();
    
    //velocity X calmers, world friction
    if(getVelocity().x > 0){
        editVelocity().x -= 0.5;
    }else if(getVelocity().x < 0){
        editVelocity().x += 0.5;
    }
    //get actual user input
    if((inputHandler->getSPACE() || inputHandler->getUP()) && isTouchingBelow && getVelocity().y == 0){
        editVelocity().y += jumpHeight;
        movement = true;
    }
    if(inputHandler->getRIGHT()){
        editVelocity().x += speed;
        movement = true;
    }
    if(inputHandler->getLEFT()){
        editVelocity().x -= speed;
        movement = true;
    }
    
    //clamp the jump speed
    if(getVelocity().y < jumpHeight){
        editVelocity().y = jumpHeight;
    }
    //clamp the running speed
    if(getVelocity().x > getMaxSpeedX()){
        editVelocity().x = getMaxSpeedX();
    }
    if(getVelocity().x < -getMaxSpeedX()){
        editVelocity().x = -getMaxSpeedX();
    }
    worldHandler->movementCheck(editPosition(), editVelocity(), editScene(), true, true);
    
    if(inputHandler->getQ() && inventoryItemDisplayAlpha < 0.9){
        inv.backwards();
        inventoryItemDisplayAlpha = 1;
    }
    
    if(inputHandler->getE() && inventoryItemDisplayAlpha < 0.9){
        inv.forwards();
        inventoryItemDisplayAlpha = 1;
    }
    
    //Item placement check
    if(inputHandler->getMOUSE1()){
        if(inv.getSelectedPos() > inv.size() || inv.isEmpty()){
            return;
        }
        //check if the item is even placeable
        if(inv.getSelected()->type->placeable){
            //get a pointer to the item you're placing
            Item* item = inv.getSelected()->type;
            //get the distance between your character and your mouse
            float distance = Math::vectorDistance(getPosition().x+SPRITE_SIZE/2, getPosition().y+SPRITE_SIZE/2, thisMouseX, thisMouseY);
            if(distance < SPRITE_SIZE*3){
                //get an instance of the tile you're hovering over
                Tile tile = *worldHandler->getTile(thisMouseX, thisMouseY);
                //make sure the tile is empty
                if(tile.id == T_sky){
                    //swap the air tile for the tileID that is dropped
                    worldHandler->getTile(thisMouseX, thisMouseY) = &worldHandler->getTiles()[item->tileID];
                    //reduce the amount held
                    //this method also handles deletion
                    if(inv.reduceSelected()){
                        inventoryItemDisplayAlpha = 1;
                    }
                }
            }
        }
    }
    
    //you can't mine whilst moving
    if(!movement){
        //if the LMB is pressed and you're not already mining, start the checks to start mining
        if(inputHandler->getMOUSE0() && !mining){
            //get the distance between the mouse and the player
            float distance = Math::vectorDistance(getPosition().x+SPRITE_SIZE/2, getPosition().y+SPRITE_SIZE/2, thisMouseX, thisMouseY);
            
            //only if the distance is less than the spritesize*3 then we should start mining
            if(distance < SPRITE_SIZE*3){
                Tile tile = *worldHandler->getTile(thisMouseX, thisMouseY);
                if(tile.solid){
                    miningTime = tile.strength;
                    selectedX = thisMouseX-(thisMouseX%SPRITE_SIZE);
                    selectedY = thisMouseY-(thisMouseY%SPRITE_SIZE);
                    mining = true;
                    timer.start();
                }
            }
        }
        //if you're currently mining then check you're still holding that LMB
        if(mining){
            int x = thisMouseX-(thisMouseX%SPRITE_SIZE);
            int y = thisMouseY-(thisMouseY%SPRITE_SIZE);
            //check if you're still on the original tile
            if(x != selectedX || y!= selectedY){
                this->stopMining();
            }else if(!inputHandler->getMOUSE0()){
                this->stopMining();
            }else{
                //if the mining is still happening
                if(timer.elapsedTime() >= miningTime){
                    inv.pickup(worldHandler->getItems()[worldHandler->getTile(thisMouseX, thisMouseY)->itemDrop], 1);
                    worldHandler->getTile(thisMouseX, thisMouseY) = &worldHandler->getTiles()[0];
                    this->stopMining();
                }
                else if(timer.elapsedTime() >= miningTime-(miningTime/4)){
                    miningLevel = 3;
                } else if(timer.elapsedTime() >= miningTime/2){
                    miningLevel = 2;
                } else if(timer.elapsedTime() >= miningTime/4){
                    miningLevel = 1;
                }
            }
        }
    }else if(mining){
        this->stopMining();
    }
}

void Player::stopMining(){
    mining = false;
    miningLevel = 0;
    timer.reset();
}

void Player::render(){
    renderInventory();
    SpriteHandler::getInstance()->get(SPRITE_CODE::S_player)->draw(this->getPosition(), SPRITE_SIZE, SPRITE_SIZE);
    miningAnimation();
}

void Player::miningAnimation(){
    //if mining draw the level of destruction over the current tile
    if(mining){
        switch(miningLevel){
            case 1:
                SpriteHandler::getInstance()->get(T_destruction1)->draw(selectedX, selectedY, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case 2:
                SpriteHandler::getInstance()->get(T_destruction2)->draw(selectedX, selectedY, SPRITE_SIZE, SPRITE_SIZE);
                break;
            case 3:
                SpriteHandler::getInstance()->get(T_destruction3)->draw(selectedX, selectedY, SPRITE_SIZE, SPRITE_SIZE);
                break;
        }
    }
}

void Player::renderInventory(){
    if(inventoryShown){
        inv.display(&text);
    }

    if(inventoryItemDisplayAlpha != 0 && !inv.isEmpty()){
        glColor4d(1,1,1,inventoryItemDisplayAlpha);
        //renders the current block
        SpriteHandler::getInstance()->get(inv.getSelected()->type->textureCode)->draw(this->getPosition().x, this->getPosition().y-SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
        glColor4d(1,1,1, inventoryItemDisplayAlpha);
        //renders the text showing how much there is
        text.draw(std::to_string(inv.getSelected()->num), getPosition().x, (getPosition().y)-4);
        inventoryItemDisplayAlpha -= 0.005;
        glColor4d(1, 1, 1, 1);
   }
}

void Player::showInventory(){
    inventoryShown = !inventoryShown;
}
