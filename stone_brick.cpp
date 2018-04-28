#include "headers/stone_brick.h"

StoneBrick::StoneBrick() : Brick(2), crack_texture_(NULL) {}

void StoneBrick::decreaseDurability() {
    Brick::decreaseDurability();
    if (getDurability() == 1 && crack_texture_)
        texture_ = crack_texture_;
}

void StoneBrick::setCrackTexture(Texture crack_texture) {
    crack_texture_ = crack_texture;
}