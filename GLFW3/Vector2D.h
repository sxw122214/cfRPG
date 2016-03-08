//
//  Vector2D.h
//  GLFW3
//
//  Created by William Meaton on 07/12/2015.
//  Copyright © 2015 WillMeaton.uk. All rights reserved.
//

#ifndef Vector2D_h
#define Vector2D_h
#include <cmath>
namespace Math {
    class Vector2D{
    public:
        float x, y;
        Vector2D(float x, float y){
            this->x = x;
            this->y = y;
        }
        
        //ADD, dot, scale, subtract, 
        Vector2D(){}
        ~Vector2D(){}
        inline friend bool operator== (const Vector2D& v1, const Vector2D& v2){
            if(v1.x == v2.x && v1.y == v2.y){
                return true;
            }
            return false;
        }
        
        inline friend bool operator!= (const Vector2D& v1, const Vector2D& v2){
            return !(v1 == v2);
        }
        
        inline friend void operator+= (Vector2D& v1, const Vector2D& v2){
            v1 = v1+v2;
            return;
        }
        
        inline Vector2D& operator+ (const Vector2D& v){
            this->x += v.x;
            this->y += v.y;
            return *this;
        }
        
        inline Vector2D& operator= (const Vector2D& v){
            this->x = v.x;
            this->y = v.y;
            return *this;
        }
        
        inline Vector2D& operator* (const Vector2D& v){
            this->x *= v.x;
            this->y *= v.y;
            return *this;
        }
        
        inline Vector2D& operator*(float n){
            this->x *= n;
            this->y *= n;
            return *this;
        }
        
        friend inline void operator*= (Vector2D& v1, const Vector2D& v2){
            v1 = v1*v2;
            return;
        }
        
        inline Vector2D& operator- (const Vector2D& v) {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }
        
        inline Vector2D& operator/ (const Vector2D& v) {
            this->x /= v.x;
            this->y /= v.y;
            return *this;
        }
        
        inline Vector2D& operator/ (float n){
            this->x /= n;
            this->y /= n;
            return *this;
        }
        
        friend inline void operator/= (Vector2D& v1, const Vector2D& v2){
            v1 = v1/v2;
            return;
        }
            
        //normalise
        inline Vector2D& normalise(){
            float length = (float)sqrt(this->x*this->x + this->y*this->y);
                if(length > 0) {
                    this->x/= length;
                    this->y/= length;
                }
            return *this;
        }

    };
}
#endif /* Vector2D_h */