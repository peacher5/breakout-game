#include "headers/mouse.h"

void setMouseVisible(bool toggle) {
    // Show/hide cursor in the window.
    SDL_ShowCursor(toggle);
    // Confined cursor to the window.
    if (toggle)
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    else
        SDL_WM_GrabInput(SDL_GRAB_ON);
}

void setMouseX(int mouse_x) {
    // Set mouse x position (y position is not used when hiding cursor)
    SDL_WarpMouse(mouse_x, 0);
}

int getMouseX() {
    int mouse_x;
    // Get only mouse x position
    SDL_GetMouseState(&mouse_x, NULL);
    return mouse_x;
}

void getMousePosition(int* mouse_x, int* mouse_y) {
    // Get mouse x, y position
    SDL_GetMouseState(mouse_x, mouse_y);
}

bool isLeftClickPressed() {
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1);
}