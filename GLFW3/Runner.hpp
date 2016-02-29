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
    double currentTime, lastTime;
    bool fps(int framerate);
    static int keysPressed;
    static int mbsPressed;
public:
    static float r, g, b, a;
    static float windowWidth, windowHeight;
    Runner(float windowWidth, float windowHeight, int frameRate, const char* title, BaseCore* c);
    ~Runner(){};
    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
};

#endif /* Runner_hpp */