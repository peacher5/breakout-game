#include "headers/mouse.h"

void getMousePosition(int* mouse_x, int* mouse_y) {
    // Get mouse x, y position
    SDL_GetMouseState(mouse_x, mouse_y);
}

bool isLeftClickPressed() {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
}