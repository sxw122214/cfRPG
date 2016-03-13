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
#include "WorldHandler.hpp"

class GameObject{
    //holds the GO's position, scene and velocity
    Math::Vector2D position, scene, velocity;
    
    //the bounds used in collision, not really used now
    Graphics::Rect bounds;
    //the visibility of the GO
    bool visible = false;
    float gravityStrength = 2;
protected:
    GameObject(const Math::Vector2D &position, const Math::Vector2D &scene, const Graphics::Rect &bounds, bool visible = false);
    virtual ~GameObject(){};
public:
    //returns if the GO is visible
    const bool& isVisible();
    
    //returns the position for looking and editing
    const Math::Vector2D& getPosition();
    Math::Vector2D& editPosition();
    
    //returns the current scene for looking and editing
    const Math::Vector2D& getScene();
    Math::Vector2D& editScene();
    
    //returns the current velocity for looking and editing
    const Math::Vector2D& getVelocity();
    Math::Vector2D& editVelocity();
    
    //setters for the position and sceness
    void setPosition(const Math::Vector2D &v);
    void setPosition(const float &x, const float &y);
    void setScene(const Math::Vector2D &v);
    void setScene(const float &x, const float &y);

    
    //the virtual methods used to call down the chain
    virtual void update() = 0;
    virtual void render() = 0;
    
    //this handles the gravity of the GO's in the world
    void gravity();
};

#endif /* GameObject_hpp */
