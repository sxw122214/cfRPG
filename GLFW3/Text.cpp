//
//  Text.cpp
//  Project2
//
//  Created by William Meaton on 17/03/2016.
//  Copyright © 2016 WillMeaton.uk. All rights reserved.
//

#include "Text.hpp"


Text::Text(int size) : size(size){
    if(!(font = dtx_open_font_glyphmap("data/serif_s24.glyphmap"))) {
        std::cout << "failed to open font" << std::endl;
    }
    dtx_use_font(font, size);
}

void Text::draw(const std::string &str, float x, float y){
    glPushMatrix();
    //flipped because the library is odd
    glRotatef(180.0f,0.0f,0.0f,1.0f);
    glScalef(-1.0f,1.0f,1.0f);
    //-y because of the flip
    glTranslatef(x, -y, 0);
    glColor3f(0, 0, 0);
    dtx_string(str.c_str());
    glPopMatrix();
}

void Text::draw(const std::string &str, const Math::Vector2D &v){
    this->draw(str, v.x, v.y);
}

void Text::setSize(int size){
    this->size = size;
}