#include <cmath>
#include "headers/object.h"

Object::Object(float width, float height) :
    x_(0), y_(0), width_(width), height_(height), velX_(0), velY_(0), texture_(NULL) {}

Object::Object(float x, float y, float width, float height) :
    x_(x), y_(y), width_(width), height_(height), velX_(0), velY_(0), texture_(NULL) {}

void Object::setPos(float x, float y) {
    x_ = x;
    y_ = y;
}

void Object::setX(float x) {
    x_ = x;
}

void Object::setY(float y) {
    y_ = y;
}

void Object::setWidth(float width) {
    width_ = width;
}

void Object::setSize(float width, float height) {
    width_ = width;
    height_ = height;
}

void Object::setHeight(float height) {
    height_ = height;
}

void Object::setVelX(float velX) {
    velX_ = velX;
}

void Object::setVelY(float velY) {
    velY_ = velY;
}

void Object::setTexture(Texture texture) {
    texture_ = texture;
}

float Object::getX() {
    return x_;
}

float Object::getY() {
    return y_;
}

float Object::getWidth() {
    return width_;
}

float Object::getHeight() {
    return height_;
}

float Object::getVelX() {
    return velX_;
}

float Object::getVelY() {
    return velY_;
}

void Object::drawTexture() {
    if (texture_)
        cpDrawTexture(x_, y_, width_, height_, texture_);
}

void Object::move() {
    x_ += velX_;
    y_ += velY_;
}

CollisionSide Object::isCollide(Object object) {
    /*  Collision Detection between this object and another object
    Return collision side of this object  */

    float w = (getWidth() + object.getWidth()) / 2;
    float h = (getHeight() + object.getHeight()) / 2;
    float dx = (getX() + getWidth() / 2) - (object.getX() + object.getWidth() / 2);
    float dy = (getY() + getHeight() / 2) - (object.getY() + object.getHeight() / 2);

    // Collision detect
    if (fabs(dx) <= w && fabs(dy) <= h) {
        float wy = w * dy;
        float hx = h * dx;

        if (wy > hx) {
            if (wy > -hx)
                return CollideTop;
            else
                return CollideRight;
        } else {
            if (wy > -hx)
                return CollideLeft;
            else
                return CollideBottom;
        }
    }
    // No collision detect
    return NoCollide;
}