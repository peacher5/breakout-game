#ifndef BARRIER_BRICK_H
#define BARRIER_BRICK_H

#include "brick.h"

class BarrierBrick: public Brick {
    public:
        BarrierBrick();

        void decreaseDurability();
};

#endif // BARRIER_BRICK_H