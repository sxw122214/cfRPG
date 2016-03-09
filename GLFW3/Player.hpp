//
//  Player.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Creature.hpp"
#include "Handlers.h"
#include "Timer.hpp"

class Player : public GameObject{
public:
    Player(const Math::Vector2D &scene, const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible);
    virtual void render();
    virtual void update();
    float speed = 8;
    std::shared_ptr<WorldHandler>  worldHandler;
    std::shared_ptr<InputHandler> inputHandler;
    bool mining = false;
    Math::Timer timer;
};

#endif /* Player_hpp */
