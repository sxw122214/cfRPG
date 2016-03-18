//
//  State.cpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "State.hpp"

int State::currentStateNum;
std::vector<State*> State::states;

State* State::getCurrentState(){
    return states[currentStateNum];
}

void State::setState(int statenum){
    currentStateNum = statenum;
}

void State::addState(State *s){
    states.push_back(s);
}