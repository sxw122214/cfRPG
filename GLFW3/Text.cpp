//
//  Text.cpp
//  Project2
//
//  Created by William Meaton on 17/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Text.hpp"

namespace Graphics {
    Text::Text(){
        
    }
    
    Text::Text(int size, bool load) : size(size){
        if(load){
            this->loadGlyphmap();
        }
    }

    void Text::draw(const std::string &str, float x, float y){
        glPushMatrix();
        //flipped because the library is odd
        glRotatef(180.0f,0.0f,0.0f,1.0f);
        glScalef(-1.0f,1.0f,1.0f);
        //-y because of the flip
        glTranslatef(x, -y, 0);
        dtx_string(str.c_str());
        glPopMatrix();
    }

    void Text::draw(const std::string &str, const Math::Vector2D &v){
        this->draw(str, v.x, v.y);
    }

    void Text::setSize(int size){
        this->size = size;
    }
    
    void Text::loadGlyphmap(){
        loaded = (font = dtx_open_font_glyphmap("data/serif_s24.glyphmap"));
        if(!loaded){
            std::cout << "failed to open font" << std::endl;
            return;
        }
        dtx_use_font(font, size);
    }
}