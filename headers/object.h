#ifndef OBJECT_H
#define OBJECT_H

#include "cp_functions.h"

class Object {
    protected:
        float x_, y_, width_, height_;
    public:
        Object(float x, float y, float width, float height);

        void setX(float x);
        void setY(float y);

        float getX();
        float getY();
        float getWidth();
        float getHeight();
        void drawTexture(Texture texture);
};

#endif // OBJECT_H