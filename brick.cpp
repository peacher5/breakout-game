#include <iostream>
#include "headers/brick.h"

Brick::Brick(int durability) : Object(0, 0, 0, 0), durability_(durability), score_(0) {}

Brick::Brick() : Object(0, 0, 0, 0), durability_(1), score_(0) {}

void Brick::setScore(int score) {
    score_ = score;
}

void Brick::decreaseDurability() {
    if (durability_)
        durability_--;
}

int Brick::getScore() {
    return score_;
}

int Brick::getDurability() {
    return durability_;
}