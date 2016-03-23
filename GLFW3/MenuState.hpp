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
#include "Types.h"
#include "Handlers.h"

class MenuState : public State{
    
public:
    MenuState(){
        text.loadGlyphmap(24);
    };
    virtual ~MenuState();
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    virtual void exitCalled();
    //text for explaining the game
    Graphics::Text text;
    //user word selection
    std::string selection;
};

#endif /* MenuState_hpp */
