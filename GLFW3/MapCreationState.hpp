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

class MapCreationState : public State{
public:
    MapCreationState();
    virtual ~MapCreationState();
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    int y = 0;
    int x = 0;
    int currentTexture = 0;
    
    std::shared_ptr<InputHandler> iH;
    std::shared_ptr<WorldHandler> wH;


    
};

#endif /* MapCreationState_hpp */
