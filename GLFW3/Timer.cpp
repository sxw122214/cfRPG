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
        running = true;
    }
    void Timer::stop(){
        endTime = clock();
        running = false;
    }
    void Timer::reset(){
        running = false;
        beginTime = 0;
        endTime = 0;
    }
    unsigned long Timer::elapsedTime(){
        if(running){
            return ((unsigned long) clock() - beginTime)/CLOCKS_PER_SEC;
        }
        return ((unsigned long) endTime - beginTime)/CLOCKS_PER_SEC;
    }
    bool Timer::isRunning(){
        return running;
    }
}