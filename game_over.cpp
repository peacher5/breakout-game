#include <string>
#include "headers/global.h"
#include "headers/in_game.h"

extern Font rsu_24_font;
extern Texture game_over_overlay_texture;
extern GameScene next_scene;
extern int score;
extern bool quit;

void showGameOverScene() {
    Event event;
    while (true) {
        // Show mouse cursor
        setMouseVisible(true);

        cpClearScreen();

        // In-Game Background
        drawInGameTexture();

        // Game Over Overlay Background
        cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, game_over_overlay_texture);

        // Final Score Text
        cpDrawText(255, 255, 255, 255, WINDOW_WIDTH / 2, 224,
                ("คุณทำได้ " + to_string(score) + " คะแนน").c_str(), rsu_24_font, true);

        // Update Screen
        cpSwapBuffers();

        // Handle events
        while (cbPollEvent(&event)) {
            if (event.type == QUIT) {
                quit = true;
                return;
            }
            // When user press left click (TEST)
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                next_scene = InGame;
                return;
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}