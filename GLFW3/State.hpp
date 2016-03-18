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
#include <vector>
enum STATES{
    menu = 0,
    game = 1,
    mapeditor = 2
};

class State{
protected:
    //don't allow creation of this class
    State(){};
    State(State const&){};
    State& operator=(State const&){ return *this; };
    virtual ~State(){};
    //hold all the states
    static std::vector<State*> states;
    //which one is currently selected
    static int currentStateNum;
public:
    //returns the current state
    static State* getCurrentState();
    //add a new state to the vector
    static void addState(State*);
    //set a state to one
    static void setState(int statenum);
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void setup() = 0;
    virtual void loadWorld(int world){};
    virtual void keyPressed(int key){};
    virtual void exitCalled(){};
};
#endif /* State_hpp */