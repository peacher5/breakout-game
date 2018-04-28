#ifndef STONE_BRICK_H
#define STONE_BRICK_H

#include "brick.h"

class StoneBrick: public Brick {
    private:
        Texture crack_texture_;
    public:
        StoneBrick();

        void decreaseDurability();
        void setCrackTexture(Texture crack_texture);
};

#endif // STONE_BRICK_H