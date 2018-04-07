#include "headers/global.h"

extern Font rsu_30_font;
extern GameScene next_scene;

void showGameOverScene() {
    cpClearScreen();

    cpDrawText(255, 255, 255, 255, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
               "Game Over!", rsu_30_font, true);

    // Update Screen
    cpSwapBuffers();
    cpDelay(5000);
    next_scene = InGame;
}