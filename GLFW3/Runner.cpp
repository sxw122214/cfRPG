//
//  Runner.cpp
//  GLFW3
//
//  Created by William Meaton on 09/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#include "Runner.hpp"
float Runner::windowWidth = 0;
float Runner::windowHeight = 0;
float Runner::r = 1;
float Runner::g = 1;
float Runner::b = 1;
float Runner::a = 1;

Runner::Runner(float windowWidth, float windowHeight, int frameRate,const char* title,BaseCore* c){
    Runner::windowWidth = windowWidth;
    Runner::windowHeight = windowHeight;
    //assign the core to the pointer
    this->c = c;
    
    //get the window from the core
    GLFWwindow* window = c->getWindow();
    //sets the event call back method in basecore
    //set the error method in basecore
    glfwSetErrorCallback(error_callback);
    //if it fails then exit
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }
    //stop the window from being resizeable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //create the window using the height and stuff
    window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
    //set a userpointer for the window to this version of Runner
    glfwSetWindowUserPointer(window, this);
    //set the key_callback method
    glfwSetKeyCallback(window, key_callback);
    //set mousepressed callback
    glfwSetMouseButtonCallback(window, mouse_callback);
    //set cursor call back
    glfwSetCursorPosCallback(window, cursor_callback);
    //if the window is dead, stop the program
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //sets the context to the window
    glfwMakeContextCurrent(window);
    //sets the intervals of buffer swaps
    glfwSwapInterval(1);
    //call setup for first time run
    c->setup();
    //the game loop
    glClearColor(r, g, b, a);
    while (!glfwWindowShouldClose(window))
    {
        int iconified = glfwGetWindowAttrib(window, GLFW_ICONIFIED);
        if(iconified == 1){
            glfwWaitEvents();
        }
        if(fps(frameRate)){
            continue;
        }
        int width, height;
        //this allows GLtransparancy
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //set view port, allows pixeltopixel things
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        //clear the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //set the ortho to pixels so it can be used like processing
        glOrtho(0.f, windowWidth, windowHeight, 0.f, -1.f, 1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //call update and then draw if the window isn't iconified
        if(iconified != 1){
            //draw
            c->draw();
        }
        //swap the buffers
        glfwSwapBuffers(window);
        if(iconified != 1){
            c->update();
        }
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

bool Runner::fps(int framerate)
{
    currentTime = glfwGetTime();
    
    if(currentTime - lastTime >= 1.0 / framerate)
    {
        lastTime = currentTime;
        return true;
    }
    return false;
}


void Runner::error_callback(int error, const char* description){
    fputs(description, stderr);
}

void Runner::cursor_callback(GLFWwindow* window, double xpos, double ypos){
    void* data = glfwGetWindowUserPointer(window);
    Runner* r = static_cast<Runner*>(data);
    r->c->mouseX = xpos;
    r->c->mouseY = ypos;
}

void Runner::mouse_callback(GLFWwindow *window, int button, int action, int mods){
    void* data = glfwGetWindowUserPointer(window);
    Runner* r = static_cast<Runner*>(data);
    if(action == GLFW_PRESS){
        r->c->mousePressed(button);
        r->c->mouseIsPressed = true;
        r->c->mouseButton = button;
        return;
    }
    if(action == GLFW_RELEASE){
        r->c->mouseReleased(button);
        r->c->mouseIsPressed = false;
        r->c->mouseButton = -1;
        return;
    }
}

void Runner::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    void* data = glfwGetWindowUserPointer(window);
    Runner* r = static_cast<Runner*>(data);
    if(action == GLFW_PRESS){
        r->c->keyIsPressed = true;
        r->c->keyCode = key;
        r->c->keyPressed(key);
        return;
    }
    if(action == GLFW_RELEASE){
        r->c->keyIsPressed = false;
        r->c->keyCode = 0;
        r->c->keyReleased(key);
        return;
    }
}
