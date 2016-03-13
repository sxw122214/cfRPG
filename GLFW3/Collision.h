//
//  Collision.h
//  Project2
//
//  Created by William Meaton on 26/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Collision_h
#define Collision_h
#include "Rect.h"
#include "Triangle.h"
#include <vector>
namespace Math {
    struct lineCollide{
        Math::Vector2D v1, v2;
        lineCollide(const Math::Vector2D &v1, const Math::Vector2D &v2);
    };
    
    //this method checks a proposed position and returns a corrected position
    Math::Vector2D lineCollisionCheckX(const Math::Vector2D &originalPosition, const Math::Vector2D &proposedMovement, const lineCollide &lc);
    
    Math::Vector2D lineCollisionCheckY(const Math::Vector2D &originalPosition, const Math::Vector2D &proposedMovement, const lineCollide &lc);
    
    //returns if v3 is inside of v1-v2
    bool isInsideQuad(const Vector2D &v1, const Vector2D &v2, const Vector2D &v3);
    bool isInsideQuad(const Vector2D &point, const Vector2D &v, float w, float h);
    bool isInsideQuad(float x1, float y1, float x2, float y2, float x3, float y3);
    
    //returns the sign of the vectors
    float signVector(float x1, float y1, float x2, float y2, float x3, float y3);
    float signVector(const Vector2D &v1, const Vector2D &v2, const Vector2D &v3);
    float signVector(const Graphics::Triangle &t);
    
    //returns if point is inside of the triangle v1, v2, v3
    bool isInsideTriangle(const Vector2D &point, const Vector2D &v1, const Vector2D &v2, const Vector2D &v3);
    bool isInsideTriangle(const Vector2D &point, const Graphics::Triangle &t);
    
    //returns the distance between v1 and v2
    float vectorDistance(const Vector2D& v1, const Vector2D& v2);
    float vectorDistance(float x1, float y1, float x2, float y2);
    
    //volision work, WIP
    std::vector<Math::Vector2D> collisionCheck(const Graphics::Rect &r1, const Graphics::Rect &r2);
    std::vector<Math::Vector2D> collisionCheck(const Math::Vector2D &point, const Graphics::Rect &r2);
}

#endif /* Collision_h */
