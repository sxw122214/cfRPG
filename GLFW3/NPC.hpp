//
//  NPC.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef NPC_hpp
#define NPC_hpp

#include <stdio.h>
#include "Creature.hpp"

class NPC : public Creature{
protected:
    NPC(const Math::Vector2D &position, const Math::Vector2D &scene, const Graphics::Rect &bounds, bool visible, float health);
    
    //Used to 'talk' to other GO's
    //finds a distance and does a job depending
    virtual void talk(GameObject*) = 0;
};

#endif /* NPC_hpp */
