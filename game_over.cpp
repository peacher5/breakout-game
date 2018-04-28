#include <string>
#include "headers/global.h"
#include "headers/in_game.h"
#include "headers/button.h"
#include "headers/scoreboard.h"
#include "headers/main_menu.h"

extern Font rsu_20_font, rsu_24_font;
extern Sound button_pressed_sound;
extern Texture game_over_overlay_texture, all_lv_clear_overlay_texture;
extern Texture play_again_button_texture, play_again_button_hover_texture, play_again_button_pressed_texture;
extern Texture back_button_texture, back_button_hover_texture, back_button_pressed_texture;
extern Texture quit_button_texture, quit_button_hover_texture, quit_button_pressed_texture;
extern GameScene scene;
extern bool quit;

extern int score;
extern bool is_all_clear;

void showGameOverScene() {
    Event event;
    ScoreBoard scoreboard;

    scoreboard.write(score);

    Button play_again_btn(108, 547, 168, 51);
    Button back_btn(316, 547, 168, 51);
    Button quit_btn(524, 547, 168, 51);

    play_again_btn.setTexture(play_again_button_texture);
    play_again_btn.setHoverTexture(play_again_button_hover_texture);
    play_again_btn.setPressedTexture(play_again_button_pressed_texture);

    back_btn.setTexture(back_button_texture);
    back_btn.setHoverTexture(back_button_hover_texture);
    back_btn.setPressedTexture(back_button_pressed_texture);

    quit_btn.setTexture(quit_button_texture);
    quit_btn.setHoverTexture(quit_button_hover_texture);
    quit_btn.setPressedTexture(quit_button_pressed_texture);

    while (true) {

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

        // Buttons
        play_again_btn.drawTexture();
        back_btn.drawTexture();
        quit_btn.drawTexture();

        // Update Screen
        cpSwapBuffers();

        // Handle events
        while (cbPollEvent(&event)) {
            if (event.type == QUIT) {
                quit = true;
                deleteBricks();
                return;
            }
            if (event.type == KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                scene = MainMenu;
                deleteBricks();
                return;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (play_again_btn.isHover()) {
                    scene = InGame;
                    cpPlaySound(button_pressed_sound);
                    deleteBricks();
                    return;
                }
                if (back_btn.isHover()) {
                    scene = MainMenu;
                    cpPlaySound(button_pressed_sound);
                    deleteBricks();
                    return;
                }
                if (quit_btn.isHover()) {
                    quit = true;
                    cpPlaySound(button_pressed_sound);
                    fadeOutScene();
                    deleteBricks();
                    return;
                }
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}