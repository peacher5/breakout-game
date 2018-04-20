#include "headers/global.h"
#include "headers/button.h"

extern Texture main_menu_bg_texture, black_bg_texture;
extern Texture play_button_texture, play_button_hover_texture, play_button_pressed_texture;
extern Texture highscore_button_texture, highscore_button_hover_texture, highscore_button_pressed_texture;
extern Texture quit_button_texture, quit_button_hover_texture, quit_button_pressed_texture;
extern GameScene scene;
extern bool quit;

void fadeOutScene() {
    int opacity = 0;
    while (opacity < 80) {
        // Animate dimming screen
        cpDrawTextureAlpha(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black_bg_texture, opacity);
        cpSwapBuffers();
        opacity += 2;
        cpDelay(10);
    }
}

void showMainMenuScene() {
    Event event;

    Button play_btn(288, 290, 220, 67);
    Button highscore_btn(288, 397, 220, 67);
    Button quit_btn(288, 504, 220, 67);

    play_btn.setTexture(play_button_texture);
    play_btn.setHoverTexture(play_button_hover_texture);
    play_btn.setPressedTexture(play_button_pressed_texture);

    highscore_btn.setTexture(highscore_button_texture);
    highscore_btn.setHoverTexture(highscore_button_hover_texture);
    highscore_btn.setPressedTexture(highscore_button_pressed_texture);

    quit_btn.setTexture(quit_button_texture);
    quit_btn.setHoverTexture(quit_button_hover_texture);
    quit_btn.setPressedTexture(quit_button_pressed_texture);

    while (true) {
        cpClearScreen();

        // Background
        cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, main_menu_bg_texture);

        // Buttons
        play_btn.drawTexture();
        highscore_btn.drawTexture();
        quit_btn.drawTexture();

        // Update Screen
        cpSwapBuffers();

        // Handle events
        while (cbPollEvent(&event)) {
            if (event.type == QUIT) {
                quit = true;
                return;
            }
            if (event.type == KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                fadeOutScene();
                return;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (play_btn.isHover()) {
                    scene = InGame;
                    fadeOutScene();
                    return;
                }
                if (highscore_btn.isHover()) {
                    scene = HighScore;
                    return;
                }
                if (quit_btn.isHover()) {
                    quit = true;
                    fadeOutScene();
                    return;
                }
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}