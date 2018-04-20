#include <string>
#include "headers/global.h"
#include "headers/button.h"
#include "headers/scoreboard.h"

extern Font rsu_20_font;
extern Sound button_pressed_sound;
extern Texture high_score_bg_texture;
extern Texture back_button_texture, back_button_hover_texture, back_button_pressed_texture;
extern GameScene scene;
extern bool quit;

void showHighScoreScene() {
    Event event;
    ScoreBoard scoreboard;

    Button back_btn(288, 540, 220, 67);

    back_btn.setTexture(back_button_texture);
    back_btn.setHoverTexture(back_button_hover_texture);
    back_btn.setPressedTexture(back_button_pressed_texture);

    while (true) {
        cpClearScreen();

        // Background
        cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, high_score_bg_texture);

        // Buttons
        back_btn.drawTexture();

        // High Score Board
        for (int i = 0, x = 0, y = 290; i < 10; i++, y += 34) {
            if (i == 5) x = 370, y = 290;
            // Ranking index (1-10)
            cpDrawText(255, 255, 255, 255, 80 + x, y, to_string(i + 1).c_str(), rsu_20_font, true);
            // Date/Time
            cpDrawText(255, 255, 255, 255, 198 + x, y,
                scoreboard.getDateTimeByIndex(i).c_str(),rsu_20_font, true);
            // High Score
            cpDrawText(255, 255, 255, 255, 328 + x, y,
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
            if (event.type == KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                scene = MainMenu;
                return;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (back_btn.isHover()) {
                    scene = MainMenu;
                    cpPlaySound(button_pressed_sound);
                    return;
                }
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}