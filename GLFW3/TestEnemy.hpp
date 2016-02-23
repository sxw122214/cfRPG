//
//  TestEnemy.hpp
//  Project2
//
//  Created by William Meaton on 07/02/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef TestEnemy_hpp
#define TestEnemy_hpp

#include <stdio.h>
#include "NPC.hpp"
#include "WorldHandler.hpp"


class TestEnemy : public NPC{
public:
    TestEnemy(const Math::Vector2D &position, const Math::Vector2D &scene, const Graphics::Rect &bounds, bool visible, float health);
    virtual void render();
    virtual void update();
    virtual void talk(GameObject* go);
};

#endif /* TestEnemy_hpp */
