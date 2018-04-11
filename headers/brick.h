#ifndef BRICK_H
#define BRICK_H

#include "object.h"

class Brick: public Object {
    protected:
        int durability_, score_;
        Texture crack_texture_;
    public:
        Brick();

        void setScore(int score);
        void setDurability(int durability);
        void decreaseDurability();
        void setCrackTexture(Texture crack_texture);

        int getScore();
        int getDurability();
};

#endif // BRICK_H