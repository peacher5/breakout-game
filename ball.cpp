#include "headers/ball.h"

Ball::Ball() :
    Object(0, 0, 0, 0), isOnScreen_(true) {}

Ball::Ball(float width, float height) :
    Object(0, 0, width, height), isOnScreen_(true) {}

void Ball::invertVelX() {
    velX_ = -velX_;
}

void Ball::invertVelY() {
    velY_ = -velY_;
}

void Ball::setIsOnScreen(bool isOnScreen) {
    isOnScreen_ = isOnScreen;
}

bool Ball::isOnScreen() {
    return isOnScreen_;
}