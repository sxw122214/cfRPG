//
//  State.hpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>

class State{
protected:
    //don't allow creation of this class
    State(){};
    State(State const&){};
    //State& operator=(State const&){};
    virtual ~State(){};
public:
    static State* currentState;
    static State* getCurrentState();
    static void setState(State*);
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
};
#endif /* State_hpp */
