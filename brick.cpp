#include <iostream>
#include "headers/brick.h"

Brick::Brick() : Object(0, 0, 0, 0), durability_(1), score_(0), crack_texture_(NULL) {}

void Brick::setScore(int score) {
    score_ = score;
}

void Brick::setDurability(int durability) {
    if (durability > 0)
        durability_ = durability;
}

void Brick::decreaseDurability() {
    if (durability_) {
        durability_--;
        if (durability_ == 1 && crack_texture_)
            texture_ = crack_texture_;
    }
}

void Brick::setCrackTexture(Texture crack_texture) {
    crack_texture_ = crack_texture;
}

void Brick::setBrickType(BrickType type) {
    type_ = type;
}

int Brick::getScore() {
    return score_;
}

int Brick::getDurability() {
    return durability_;
}

BrickType Brick::getBrickType() {
    return type_;
}