//
//  Timer.cpp
//  Project2
//
//  Created by William Meaton on 26/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Timer.hpp"
namespace Math{
    Timer::Timer(bool startNow){
        beginTime = clock();
    }
    Timer::Timer(){
        
    }
    void Timer::start(){
        beginTime = clock();
        started = true;
        running = true;
    }
    void Timer::stop(){
        endTime = clock();
        running = false;
    }
    void Timer::reset(){
        running = false;
        started = false;
        beginTime = 0;
        endTime = 0;
    }

    unsigned long Timer::elapsedTime(){
        if(running){
            return ((unsigned long) clock() - beginTime)/100000;
            }
            return ((unsigned long) endTime - beginTime)/100000;
    }
    bool Timer::isRunning(){
        return running;
    }
    
    bool Timer::isStarted(){
        return started;
    }
}