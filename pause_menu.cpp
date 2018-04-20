#include "headers/global.h"
#include "headers/in_game.h"
#include "headers/button.h"
#include "headers/main_menu.h"

extern Sound button_pressed_sound;
extern Texture pause_menu_bg_texture;
extern Texture resume_button_texture, resume_button_hover_texture, resume_button_pressed_texture;
extern Texture back_button_texture, back_button_hover_texture, back_button_pressed_texture;
extern Texture quit_button_texture, quit_button_hover_texture, quit_button_pressed_texture;
extern GameScene scene;
extern bool quit;

void showPauseMenuScene() {
    Event event;

    Button resume_btn(288, 272, 220, 67);
    Button back_btn(288, 363, 220, 67);
    Button quit_btn(288, 454, 220, 67);

    resume_btn.setTexture(resume_button_texture);
    resume_btn.setHoverTexture(resume_button_hover_texture);
    resume_btn.setPressedTexture(resume_button_pressed_texture);

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

        // Pause Menu Overlay
        cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, pause_menu_bg_texture);

        // Buttons
        resume_btn.drawTexture();
        back_btn.drawTexture();
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
                return;
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                if (resume_btn.isHover()) {
                    cpPlaySound(button_pressed_sound);
                    return;
                }
                if (back_btn.isHover()) {
                    scene = MainMenu;
                    cpPlaySound(button_pressed_sound);
                    return;
                }
                if (quit_btn.isHover()) {
                    quit = true;
                    cpPlaySound(button_pressed_sound);
                    fadeOutScene();
                    return;
                }
            }
        }

        // Wait 10 ms
        cpDelay(10);
    }
}