//
//  Runner.hpp
//  GLFW3
//
//  Created by William Meaton on 09/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#ifndef Runner_hpp
#define Runner_hpp

#include "BaseCore.hpp"
class Runner{
    BaseCore* c;
    float currentTime, lastTime;
    bool fps(int framerate);
public:
    static float windowWidth, windowHeight;
    Runner(float windowWidth, float windowHeight, int frameRate, const char* title, BaseCore* c);
    
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif /* Runner_hpp */