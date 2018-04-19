#ifndef BUTTON_H
#define BUTTON_H

#include "object.h"

class Button: public Object {
    protected:
        Texture hover_texture_, pressed_texture_;
    public:
        Button(float x, float y, float width, float height);

        void setHoverTexture(Texture hover_texture);
        void setPressedTexture(Texture pressed_texture);

        Texture getHoverTexture();
        Texture getPressedTexture();
        bool isHover();
        void drawTexture();
};

#endif // BUTTON_H