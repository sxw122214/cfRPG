//
//  Timer.hpp
//  Project2
//
//  Created by William Meaton on 26/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <time.h>


namespace Math {
    class Timer{
    private:
        unsigned long beginTime = 0;
        unsigned long endTime = 0;
        bool running = false, started = false;
    public:
        Timer(bool);
        Timer();
        void start();
        void stop();
        void reset();
        bool isRunning();
        bool isStarted();
        float elapsedTime();
    };
}

#endif /* Timer_hpp */
