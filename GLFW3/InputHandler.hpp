//
//  InputHandler.hpp
//  Project2
//
//  Created by William Meaton on 31/12/2015.
//
//

#ifndef InputHandler_hpp
#define InputHandler_hpp

#include <stdio.h>
#include <memory>

//this class handles keyboard input with predefined buttons
class InputHandler{
    
    static std::shared_ptr<InputHandler> instance;
    
    InputHandler(InputHandler const &s){}; // no copy constructor
    bool UP, LEFT, RIGHT, DOWN, isKeyPressed, SPACE, MOUSE0, MOUSE1, isMousePressed;
    int mouseX = 0, mouseY = 0;
public:
    InputHandler(){};
    static std::shared_ptr<InputHandler> getInstance();
    void mouseInput(int x, int y);
    int getMouseX();
    int getMouseY();
    void mouseDown(int button);
    void mouseUp(int button);
    void keyUp(int key);
    void keyDown(int key);
    bool getUP();
    bool getLEFT();
    bool getRIGHT();
    bool getDOWN();
    bool getisKeyPressed();
    bool getisMousePressed();
    bool getSPACE();
    bool getMOUSE0();
    bool getMOUSE1();
    
};


#endif /* Keyboard_hpp */
