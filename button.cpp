#include "headers/button.h"
#include "headers/mouse.h"

Button::Button(float x, float y, float width, float height)
    : Object(x, y, width, height), hover_texture_(NULL), pressed_texture_(NULL) {}

void Button::setHoverTexture(Texture hover_texture) {
    hover_texture_ = hover_texture;
}

void Button::setPressedTexture(Texture pressed_texture) {
    pressed_texture_ = pressed_texture;
}

Texture Button::getHoverTexture() {
    return hover_texture_;
}

Texture Button::getPressedTexture() {
    return pressed_texture_;
}

bool Button::isHover() {
    // Get x,y cursor position
    int mouse_x, mouse_y;
    getMousePosition(&mouse_x, &mouse_y);
    // Check if cursor is in the button
    if (mouse_x >= x_ && mouse_x <= x_ + width_ && mouse_y >= y_ && mouse_y <= y_ + height_)
        return true;
    return false;
}

void Button::drawTexture() {
    // Check to draw the right texture
    // If no texture is set then don't draw that
    if (isHover()) {
        if (pressed_texture_ && isLeftClickPressed())
            cpDrawTexture(x_, y_, width_, height_, pressed_texture_);
        else if (hover_texture_)
            cpDrawTexture(x_, y_, width_, height_, hover_texture_);
    } else if (texture_)
        cpDrawTexture(x_, y_, width_, height_, texture_);
}