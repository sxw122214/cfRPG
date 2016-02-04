//
//  Object.hpp
//  Project2
//
//  Created by William Meaton on 19/01/2016.
//
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>

class Object{
    bool visible;
protected:
    Object(bool visible = false);
public:
    virtual void render(){};
    virtual void update(){};
};

#endif /* Object_hpp */
