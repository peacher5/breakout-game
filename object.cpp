#include "headers/object.h"

Object::Object(float width, float height) :
    x_(0), y_(0), width_(width), height_(height) {}

Object::Object(float x, float y, float width, float height) :
    x_(x), y_(y), width_(width), height_(height) {}

void Object::setX(float x) {
    x_ = x;
}

void Object::setY(float y) {
    y_ = y;
}

void Object::setWidth(float width) {
    width_ = width;
}

void Object::setHeight(float height) {
    height_ = height;
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

void Object::drawTexture(Texture texture) {
    cpDrawTexture(Object::getX(), Object::getY(), Object::getWidth(), Object::getHeight(), texture);
}