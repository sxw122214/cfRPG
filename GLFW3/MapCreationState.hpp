//
//  MapCreationState.hpp
//  Project2
//
//  Created by William Meaton on 28/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef MapCreationState_hpp
#define MapCreationState_hpp

#include <stdio.h>
#include "State.hpp"
#include "Handlers.h"
#include <thread>
#include <string>
#include <iostream>
#include <fstream>

class MapCreationState : public State{
public:
    MapCreationState();
    virtual ~MapCreationState();
    virtual void setup(){};
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    virtual void loadWorld(int world);
    
    void saveMap();
    int y = 0;
    int x = 0;
    int currentTexture = 0;
    
    std::shared_ptr<InputHandler> iH;
    std::shared_ptr<WorldHandler> wH;

    //what world is loaded
    int worldLoaded;
    
    //used to show if the world has been saved
    float savedAlpha = 0;
    //text to draw updates
    Graphics::Text text;
    
};

#endif /* MapCreationState_hpp */
