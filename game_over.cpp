#include <string>
#include "headers/global.h"
#include "headers/in_game.h"
#include "headers/scoreboard.h"

extern Font rsu_20_font, rsu_24_font;
extern Texture game_over_overlay_texture, all_lv_clear_overlay_texture;
extern GameScene scene;
extern bool quit;

extern int score;
extern bool is_all_clear;

void showGameOverScene() {
    Event event;
    ScoreBoard scoreboard;

    scoreboard.write(score);

    while (true) {
        // Show mouse cursor
        setMouseVisible(true);

        cpClearScreen();

        // In-Game Background
        drawInGameTexture();

        if (is_all_clear)
            // All Level Clear Overlay Background
            cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, all_lv_clear_overlay_texture);
        else
            // Game Over Overlay Background
            cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, game_over_overlay_texture);

        // Final Score Text
        cpDrawText(255, 255, 255, 255, WINDOW_WIDTH / 2, 224,
                ("คุณทำได้ " + to_string(score) + " คะแนน").c_str(), rsu_24_font, true);

        // High Score Board
        for (int i = 0, x = 0, y = 0; i < 10; i++, y += 34) {
            if (i == 5) x = 370, y = 0;
            // Ranking index (1-10)
            cpDrawText(255, 255, 255, 255, 80 + x, 335 + y, to_string(i + 1).c_str(), rsu_20_font, true);
            // Date/Time
            cpDrawText(255, 255, 255, 255, 198 + x, 335 + y,
                scoreboard.getDateTimeByIndex(i).c_str(),rsu_20_font, true);
            // High Score
            cpDrawText(255, 255, 255, 255, 328 + x, 335 + y,
                scoreboard.getHighScoreByIndex(i).c_str(), rsu_20_font, true);
        }

        // Update Screen
        cpSwapBuffers();

        // Handle events
        while (cbPollEvent(&event)) {
            if (event.type == QUIT) {
                quit = true;
                return;
            }
            // Exit when user released ESC key
            if (event.type == KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                return;
            }
            // When user press left click (TEST)
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                scene = InGame;
                return;
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}