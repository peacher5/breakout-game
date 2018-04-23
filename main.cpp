#include <iostream>
#include <cstdlib>
#include "headers/global.h"
#include "headers/main_menu.h"
#include "headers/in_game.h"
#include "headers/game_over.h"
#include "headers/high_score.h"

// Global shared resources
Font rsu_20_font, rsu_24_font, rsu_26_font, rsu_30_font;
Music background_music;

// Main Menu
Sound button_pressed_sound;
Texture main_menu_bg_texture, black_bg_texture;
Texture play_button_texture, play_button_hover_texture, play_button_pressed_texture;
Texture highscore_button_texture, highscore_button_hover_texture, highscore_button_pressed_texture;
Texture quit_button_texture, quit_button_hover_texture, quit_button_pressed_texture;

// In-game
Sound hit_paddle_sound, hit_brick_sound, hit_top_sound, end_sound, missile_sound;
Texture paddle_texture, ball_texture, in_game_bg_texture, in_game_frame_texture;
Texture blue_brick_texture, stone_brick_texture, crack_stone_brick_texture;
Texture orange_brick_texture, red_brick_texture, yellow_brick_texture, barrier_brick_texture;
Texture blue_item_brick_texture, orange_item_brick_texture, red_item_brick_texture, yellow_item_brick_texture;
Texture missile_texture, missiles_left_icon_texture;

// Pause Menu
Texture pause_menu_bg_texture;
Texture resume_button_texture, resume_button_hover_texture, resume_button_pressed_texture;
Texture back_button_texture, back_button_hover_texture, back_button_pressed_texture;

// Game Over
Texture game_over_overlay_texture, all_lv_clear_overlay_texture;
Texture play_again_button_texture, play_again_button_hover_texture, play_again_button_pressed_texture;

// High Score
Texture high_score_bg_texture;

GameScene scene;
bool quit;

Font loadFont(const char *font_file, int font_size) {
    Font font = cpLoadFont(font_file, font_size);
    if (!font) {
        cout << "Font init failed (" << font_file << "): " << TTF_GetError() << endl;
        exit(1);
    }
    return font;
}

Music loadMusic(const char *music_file) {
    Music music = cpLoadMusic(music_file);
    if (!music) {
        cout << "Music init failed (" << music_file << "): " << Mix_GetError() << endl;
        exit(1);
    }
    return music;
}

Sound loadSound(const char *sound_file) {
    Sound sound = cpLoadSound(sound_file);
    if (!sound) {
        cout << "Sound init failed (" << sound_file << "): " << Mix_GetError() << endl;
        exit(1);
    }
    return sound;
}

Texture loadTexture(const char *filename) {
    Texture texture = cpLoadTexture(filename);
    if (!texture) {
        cout << "Texture init failed (" << filename << "): " << IMG_GetError() << endl;
        exit(1);
    }
    return texture;
}

void loadResources() {
    // Font
    rsu_20_font = loadFont("fonts/RSU_BOLD.ttf", 20);
    rsu_24_font = loadFont("fonts/RSU_BOLD.ttf", 24);
    rsu_26_font = loadFont("fonts/RSU_BOLD.ttf", 26);
    rsu_30_font = loadFont("fonts/RSU_BOLD.ttf", 30);

    // Sound & Music
    background_music = loadMusic("sounds/bgm.ogg");
    hit_paddle_sound = loadSound("sounds/hit_paddle.wav");
    hit_brick_sound = loadSound("sounds/hit_brick.wav");
    hit_top_sound = loadSound("sounds/hit_top.wav");
    missile_sound = loadSound("sounds/missile.wav");
    button_pressed_sound = loadSound("sounds/btn_pressed.wav");

    // Main Menu
    main_menu_bg_texture = loadTexture("textures/main_menu_bg.png");

    play_button_texture = loadTexture("textures/play_btn.png");
    play_button_hover_texture = loadTexture("textures/play_btn_hover.png");
    play_button_pressed_texture = loadTexture("textures/play_btn_pressed.png");

    highscore_button_texture = loadTexture("textures/high_score_btn.png");
    highscore_button_hover_texture = loadTexture("textures/high_score_btn_hover.png");
    highscore_button_pressed_texture = loadTexture("textures/high_score_btn_pressed.png");

    quit_button_texture = loadTexture("textures/quit_btn.png");
    quit_button_hover_texture = loadTexture("textures/quit_btn_hover.png");
    quit_button_pressed_texture = loadTexture("textures/quit_btn_pressed.png");

    // In-game
    in_game_bg_texture = loadTexture("textures/in_game_bg.png");
    in_game_frame_texture = loadTexture("textures/in_game_frame.png");
    black_bg_texture = loadTexture("textures/black_bg.png");

    paddle_texture = loadTexture("textures/paddle.png");
    ball_texture = loadTexture("textures/ball.png");

    blue_brick_texture = loadTexture("textures/blue_brick.png");
    orange_brick_texture = loadTexture("textures/orange_brick.png");
    red_brick_texture = loadTexture("textures/red_brick.png");
    yellow_brick_texture = loadTexture("textures/yellow_brick.png");
    stone_brick_texture = loadTexture("textures/stone_brick.png");
    crack_stone_brick_texture = loadTexture("textures/crack_stone_brick.png");
    barrier_brick_texture = loadTexture("textures/barrier_brick.png");
    blue_item_brick_texture = loadTexture("textures/blue_item_brick.png");
    orange_item_brick_texture = loadTexture("textures/orange_item_brick.png");
    red_item_brick_texture = loadTexture("textures/red_item_brick.png");
    yellow_item_brick_texture = loadTexture("textures/yellow_item_brick.png");

    missile_texture = loadTexture("textures/missile.png");
    missiles_left_icon_texture = loadTexture("textures/missiles_left_icon.png");

    // Pause Menu
    pause_menu_bg_texture = loadTexture("textures/pause_menu_overlay.png");

    resume_button_texture = loadTexture("textures/resume_btn.png");
    resume_button_hover_texture = loadTexture("textures/resume_btn_hover.png");
    resume_button_pressed_texture = loadTexture("textures/resume_btn_pressed.png");

    back_button_texture = loadTexture("textures/back_btn.png");
    back_button_hover_texture = loadTexture("textures/back_btn_hover.png");
    back_button_pressed_texture = loadTexture("textures/back_btn_pressed.png");

    // Game Over
    game_over_overlay_texture = loadTexture("textures/game_over_overlay.png");
    all_lv_clear_overlay_texture = loadTexture("textures/all_lv_clear_overlay.png");

    play_again_button_texture = loadTexture("textures/play_again_btn.png");
    play_again_button_hover_texture = loadTexture("textures/play_again_btn_hover.png");
    play_again_button_pressed_texture = loadTexture("textures/play_again_btn_pressed.png");

    // High Score
    high_score_bg_texture = loadTexture("textures/high_score_bg.png");
}

int main(int argc, char *args[]) {

    cout << "Starting..." << endl;

    if (!cpInit(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        cout << "Window Initialization Failed!" << endl;
        exit(1);
    }

    // Load fonts, sounds, music & textures
    loadResources();

    // Reduce volume of missile fire sound
    Mix_VolumeChunk(missile_sound, MIX_MAX_VOLUME / 6);

    // Loop play background music
    cpPlayMusic(background_music);

    while (!quit) {
        switch (scene) {
            case MainMenu:
                showMainMenuScene();
                break;
            case InGame:
                showInGameScene();
                break;
            case GameOver:
                showGameOverScene();
                break;
            case HighScore:
                showHighScoreScene();
                break;
        }
    }

    cpCleanUp();
    return 0;
}
