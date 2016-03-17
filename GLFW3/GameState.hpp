//
//  GameState.hpp
//  Project2
//
//  Created by William Meaton on 21/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include <stdio.h>
#include "State.hpp"
#include <vector>
#include <thread>
#include "Handlers.h"
#include "Player.hpp"
#include "TestEnemy.hpp"

class GameState : public State{
public:
    GameState(int world);
    virtual ~GameState(){
        inputHandler = nullptr;
    }
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    std::shared_ptr<InputHandler> inputHandler;
    std::shared_ptr<WorldHandler> worldHandler;
    
    std::vector<GameObject*> renderVector;
    std::vector<GameObject*> updateVector;
    
    void pushBothRU(GameObject*);
    
    //text to draw updates
    Graphics::Text text;
    float savedAlpha = 0;
    //saves the world over the currently selected one
    void saveWorld();
    
    //the current loaded world
    int worldLoaded;
    
    Player player = Player(Math::Vector2D(50, 50), Math::Vector2D(0, 0), Graphics::Rect(0, 0, 50, 250), true);
    TestEnemy t = TestEnemy(Math::Vector2D(50, 50), Math::Vector2D(0, 0), Graphics::Rect(0, 0, 50, 250), true, 50);
};
#endif /* GameState_hpp */
