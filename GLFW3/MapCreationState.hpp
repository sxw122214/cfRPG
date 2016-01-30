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

class MapCreationState : public State{
public:
    MapCreationState();
    virtual ~MapCreationState();
    void update();
    void draw();
    int y = 0;
    int x = 0;
};

#endif /* MapCreationState_hpp */
