//
//  BaseCore.hpp
//  GLFW3
//
//  Created by William Meaton on 09/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#ifndef BaseCore_hpp
#define BaseCore_hpp

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <stdlib.h>
#include "Graphics.hpp"

class BaseCore{
private:
    GLFWwindow* window;
protected:
    BaseCore(){};
    BaseCore(BaseCore const&){};
    //Needs assignemnet made private
public:
    bool keyIsPressed = false;
    bool mouseIsPressed = false;
    int mouseButton = -1;
    int keyCode = 0;
    virtual ~BaseCore(){};
    virtual void draw(){};
    virtual void setup(){};
    virtual void update(){};
    virtual void keyPressed(int key){};
    virtual void keyReleased(int key){};
    virtual void mousePressed(int button){};
    virtual void mouseReleased(int button){};
    GLFWwindow* getWindow();
};

#endif /* BaseCore_hpp */