//
//  Creature.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef Creature_hpp
#define Creature_hpp

#include <stdio.h>
#include "GameObject.hpp"

class Creature: public GameObject{
protected:
    float health;
protected:
    Creature(Math::Vector2D position, bool visible, float health);
};
#endif /* Creature_hpp */
