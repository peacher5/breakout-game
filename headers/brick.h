#ifndef BRICK_H
#define BRICK_H

#include "object.h"

class Brick: public Object {
    protected:
        int durability_;
    public:
        Brick();
        Brick(float x, float y, float width, float height, int durability);

        void setDurability(int durability);
        void decreaseDurability();

        int getDurability();
};

#endif // BRICK_H