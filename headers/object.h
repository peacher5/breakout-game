#ifndef OBJECT_H
#define OBJECT_H

#include "cp_functions.h"

class Object {
    protected:
        float x_, y_, width_, height_;
        Texture texture_;
    public:
        Object(float width, float height);
        Object(float x, float y, float width, float height);

        void setX(float x);
        void setY(float y);
        void setWidth(float width);
        void setHeight(float height);
        void setSize(float width, float height);
        void setTexture(Texture texture);

        float getX();
        float getY();
        float getWidth();
        float getHeight();
        void drawTexture();
};

#endif // OBJECT_H