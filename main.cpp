#include <iostream>
#include "headers/global.h"
#include "headers/in_game.h"
#include "headers/game_over.h"

// Global shared resources
Font rsu_20_font, rsu_24_font, rsu_26_font, rsu_30_font;
Music background_music;
Sound hit_paddle_sound, hit_brick_sound, hit_top_sound, end_sound, missile_sound;
Texture paddle_texture, ball_texture, in_game_bg_texture, in_game_frame_texture;
Texture blue_brick_texture, stone_brick_texture, crack_stone_brick_texture;
Texture game_over_overlay_texture, missile_texture, missiles_left_icon_texture;
GameScene scene;
bool quit;

bool loadResources() {
    // Font
    rsu_20_font = cpLoadFont("fonts/RSU_BOLD.ttf", 20);
    rsu_24_font = cpLoadFont("fonts/RSU_BOLD.ttf", 24);
    rsu_26_font = cpLoadFont("fonts/RSU_BOLD.ttf", 26);
    rsu_30_font = cpLoadFont("fonts/RSU_BOLD.ttf", 30);

    // Sound & Music
    background_music = cpLoadMusic("sounds/bgm.ogg");
    hit_paddle_sound = cpLoadSound("sounds/hitDown.wav");
    hit_brick_sound = cpLoadSound("sounds/hitUp.wav");
    hit_top_sound = cpLoadSound("sounds/hitTop.wav");
    end_sound = cpLoadSound("sounds/theEnd.wav");
    missile_sound = cpLoadSound("sounds/missile.wav");

    // Texture
    paddle_texture = cpLoadTexture("textures/paddle.png");
    ball_texture = cpLoadTexture("textures/ball.png");
    blue_brick_texture = cpLoadTexture("textures/blue_brick.png");
    stone_brick_texture = cpLoadTexture("textures/stone_brick.png");
    crack_stone_brick_texture = cpLoadTexture("textures/crack_stone_brick.png");
    missile_texture = cpLoadTexture("textures/missile.png");
    missiles_left_icon_texture = cpLoadTexture("textures/missiles_left_icon.png");

    in_game_bg_texture = cpLoadTexture("textures/in_game_bg.png");
    in_game_frame_texture = cpLoadTexture("textures/in_game_frame.png");

    game_over_overlay_texture = cpLoadTexture("textures/game_over_overlay.png");

   if (!rsu_24_font || !rsu_30_font || !background_music || !hit_paddle_sound || !hit_brick_sound ||
       !hit_top_sound || !end_sound || !missile_sound || !paddle_texture || !ball_texture ||
       !blue_brick_texture || !stone_brick_texture || !crack_stone_brick_texture || !in_game_bg_texture ||
       !in_game_frame_texture || !missiles_left_icon_texture)
        return false;
   return true;
}

int main(int argc, char *args[]) {

    cout << "Starting..." << endl;

    if (!cpInit(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) {
        cout << "Window Initialization Failed!" << endl;
        exit(1);
    }

    if (!loadResources()) {
        cout << "Game Initialization Failed!" << endl;
        exit(1);
    }

    // TODO: Create MainMenu scene then remove this line
    scene = InGame;

    // Loop play background music
    cpPlayMusic(background_music);

    while (!quit) {
        switch (scene) {
            case MainMenu:
                break;
            case InGame:
                showInGameScene();
                break;
            case GameOver:
                showGameOverScene();
                break;
            case HighScore:
                break;
        }
    }

    cpCleanUp();
    return 0;
}
