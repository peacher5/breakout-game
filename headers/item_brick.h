#ifndef ITEM_BRICK_H
#define ITEM_BRICK_H

#include "brick.h"

typedef enum {NoEffect, Barrier, BallsSpread, BallSpeedIncrease, MissileAmmo} ItemType;

class ItemBrick: public Brick {
    private:
        ItemType type_;
    public:
        ItemBrick();

        void setItemType(ItemType type);

        ItemType getItemType();
};

#endif // ITEM_BRICK_H