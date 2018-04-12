#include "headers/missile.h"

Missile::Missile() : Object(0, 0), is_visible_(false) {}

void Missile::setVisible(bool toggle) {
    is_visible_ = toggle;
}

int Missile::isVisible() {
    return is_visible_;
}