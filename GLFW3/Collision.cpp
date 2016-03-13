//
//  Collision.cpp
//  Project2
//
//  Created by William Meaton on 26/01/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Collision.h"

namespace Math {
    lineCollide::lineCollide(const Math::Vector2D &v1, const Math::Vector2D &v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    
    Math::Vector2D lineCollisionCheckX(const Math::Vector2D &originalPosition, const Math::Vector2D &proposedMovement, const lineCollide &lc){
        if(originalPosition.x < lc.v1.x && proposedMovement.x > lc.v1.x){
            return Math::Vector2D(lc.v1.x, proposedMovement.y);
        }
        return proposedMovement;
    }
    
    Math::Vector2D lineCollisionCheckY(const Math::Vector2D &originalPosition, const Math::Vector2D &proposedMovement, const lineCollide &lc){
        if(originalPosition.y < lc.v1.y && proposedMovement.y > lc.v1.y){
            return Math::Vector2D(proposedMovement.x, lc.v1.y);
        }
        return proposedMovement;
    }
    
    //returns if v3 is inside of v1-v2
    bool isInsideQuad(const Vector2D &point, const Vector2D &v1, const Vector2D &v2){
        if(point.x > v1.x && point.x < v2.x && point.y > v1.y && point.y < v2.y){
            return true;
        }
        return false;
    }
    
    bool isInsideQuad(const Vector2D &point, const Vector2D &v, float w, float h){
        return isInsideQuad(point, v, Vector2D(w, h));
    }
    
    bool isInsideQuad(const Vector2D &point, const Graphics::Rect &r){
        return isInsideQuad(point, r.v, Vector2D(r.w, r.h));
    }
    
    bool isInsideQuad(float &x1, float &y1, float &x2, float &y2, float &x3, float &y3){
        return isInsideQuad(Vector2D(x1, x2), Vector2D(x2, y2), Vector2D(x3, y3));
    }
    
    float signVector(float x1, float y1, float x2, float y2, float x3, float y3){
        return signVector(Vector2D(x1, y1), Vector2D(x2, y2), Vector2D(x3, y3));
    }
    
    float signVector(const Vector2D &v1, const Vector2D &v2, const Vector2D &v3){
        float det = 0.0f;
        det = ((v1.x - v3.x) * (v2.y - v3.y)) - ((v2.x - v3.x) * (v1.y - v3.y));
        return (det / 2.0f);
    }
    
    float signVector(const Graphics::Triangle &t){
        return signVector(t.v1, t.v2, t.v3);
    }
    
    bool isInsideTriangle(const Vector2D &point, const Vector2D &v1, const Vector2D &v2, const Vector2D &v3){
        bool b1, b2, b3;
        b1 = signVector(point, v1, v2) < 0.0f;
        b2 = signVector(point, v2, v3) < 0.0f;
        b3 = signVector(point, v3, v1) < 0.0f;
        return ((b1 == b2) && (b2 == b3));
    }
    
    bool isInsideTriangle(const Vector2D &point, const Graphics::Triangle &t){
        return isInsideTriangle(point, t.v1, t.v2, t.v3);
    }
    
    float vectorDistance(const Vector2D& v1, const Vector2D& v2){
        return sqrt((v1.x-v2.x)*(v1.x-v2.x)+(v1.y-v2.y)*(v1.y-v2.y));
    }
    
    float vectorDistance(float x1, float y1, float x2, float y2){
        return vectorDistance(Vector2D(x1, y1), Vector2D(x2, y2));
    }
    
    std::vector<Math::Vector2D> collisionCheck(const Graphics::Rect &r1, const Graphics::Rect &r2){
        return collisionCheck(Math::Vector2D(r1.v.y+r1.w/2, r1.v.y+r1.h/2) , r2);
    }
    
    std::vector<Math::Vector2D> collisionCheck(const Math::Vector2D &point, const Graphics::Rect &r2){
        std::vector<Math::Vector2D> collisions;
        return collisions;
    }
}