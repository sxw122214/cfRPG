//
//  Text.hpp
//  Project2
//
//  Created by William Meaton on 17/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#ifndef Text_hpp
#define Text_hpp

#include <stdio.h>
#include "dT/drawtext.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "Vector2D.h"
#include "Types.H"
namespace Graphics{
    class Text{
        struct dtx_font *font;
        int size;
        Graphics::Colour c;
    public:
        Text(int size);
        void draw(const std::string &str, float x, float y);
        void draw(const std::string &str, const Math::Vector2D &v);
        void setSize(int size);
        void setColour(const Graphics::Colour &c);
    };
}
#endif /* Text_hpp */
