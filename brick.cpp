#include "headers/brick.h"

Brick::Brick() : Object(0, 0, 0, 0), durability_(1) {}

Brick::Brick(float x, float y, float width, float height, int durability) :
    Object(x, y, width, height), durability_(durability) {
    if (durability < 1)
        durability = 1;
}

void Brick::setDurability(int durability) {
    durability_ = durability;
}

void Brick::decreaseDurability() {
    if (durability_)
        durability_--;
}

int Brick::getDurability() {
    return durability_;
}
