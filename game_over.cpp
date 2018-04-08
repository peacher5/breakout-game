#include <string>
#include "headers/global.h"
#include "headers/in_game.h"

extern Font rsu_20_font, rsu_24_font;
extern Texture game_over_overlay_texture;
extern GameScene next_scene;
extern bool quit;

extern int score;

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

        for (int i = 1, x = 0, y = 0; i <= 10; i++, y += 34) {
            if (i == 6) x = 370, y = 0;
            cpDrawText(255, 255, 255, 255, 80 + x, 335 + y, to_string(i).c_str(), rsu_20_font, true);
            cpDrawText(255, 255, 255, 255, 198 + x, 335 + y, "8/4/2561  10:12", rsu_20_font, true);
            cpDrawText(255, 255, 255, 255, 328 + x, 335 + y, "1270", rsu_20_font, true);
        }

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