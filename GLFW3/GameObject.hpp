//
//  GameObject.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "CoreMain.h"
#include "Object.hpp"

class GameObject : public Object{
protected:
    Math::Vector2D position, scene;
    bool visible;
    GameObject(const Math::Vector2D &scene,const Math::Vector2D &position, const Graphics::Rect &bounds, bool visible);
    virtual ~GameObject(){};
public:
    const Math::Vector2D& getPosition();
    void setPosition(const Math::Vector2D &v);
    void setPosition(const float &x, const float &y);
    
};

#endif /* GameObject_hpp */
