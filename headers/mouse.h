#ifndef MOUSE_H
#define MOUSE_H

#include "cp_functions.h"

void setMouseVisible(bool toggle);

void setMouseX(int mouse_x);

int getMouseX();

void getMousePosition(int* mouse_x, int* mouse_y);

#endif // MOUSE_H