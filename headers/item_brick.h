#ifndef ITEM_BRICK_H
#define ITEM_BRICK_H

#include "brick.h"

typedef enum {Nothing, BallSpread, BallSpeedIncrease, MachineGun} ItemType;

class ItemBrick: public Brick {
    protected:
        ItemType item_type_;
    public:
        ItemBrick();
        ItemBrick(float x, float y, float width, float height, ItemType item_type);

        void setItemType(ItemType item_type);

        ItemType getItemType();
};

#endif // ITEM_BRICK_H