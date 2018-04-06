#include "headers/brick.h"

Brick::Brick() : Object(0, 0, 0, 0), durability_(1), isDestroy_(false) {}

Brick::Brick(float x, float y, float width, float height, int durability) :
    Object(x, y, width, height), durability_(durability), isDestroy_(false) {
    if (durability < 1)
        durability = 1;
}

void Brick::setDurability(int durability) {
    durability_ = durability;
}

void Brick::decreaseDurability() {
    if (durability_)
        durability_--;
    else
        isDestroy_ = true;
}

int Brick::getDurability() {
    return durability_;
}

bool Brick::isDestroy() {
    return isDestroy_;
}