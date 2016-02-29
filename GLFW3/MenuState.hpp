//
//  MenuState.hpp
//  Project2
//
//  Created by William Meaton on 29/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef MenuState_hpp
#define MenuState_hpp

#include <stdio.h>
#include "State.hpp"
#include "States.h"
#include "Handlers.h"

class MenuState : public State{
    
public:
    MenuState(){};
    virtual ~MenuState();
    virtual void setup();
    virtual void update();
    virtual void draw();
    GameState* gameState;
    MapCreationState* mapCreationState;
    
};

#endif /* MenuState_hpp */
