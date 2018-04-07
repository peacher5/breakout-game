#include <iostream>
#include "headers/global.h"
#include "headers/in_game.h"

using namespace std;

// Global shared resources
Font rsu_24_font;
Sound hit_paddle_sound, hit_brick_sound, hit_top_sound, end_sound;
Texture paddle_texture, ball_texture, brick_texture, in_game_bg_texture, in_game_frame_texture;

bool loadResources() {
    // Font
    rsu_24_font = cpLoadFont("fonts/RSU_BOLD.ttf", 24);

    // Sound & Music
    hit_paddle_sound = cpLoadSound("sounds/hitDown.wav");
    hit_brick_sound = cpLoadSound("sounds/hitUp.wav");
    hit_top_sound = cpLoadSound("sounds/hitTop.wav");
    end_sound = cpLoadSound("sounds/theEnd.wav");

    // Texture
    paddle_texture = cpLoadTexture("textures/paddle.png");
    ball_texture = cpLoadTexture("textures/ball.png");
    brick_texture = cpLoadTexture("textures/brick.png");

    in_game_bg_texture = cpLoadTexture("textures/in_game_bg.png");
    in_game_frame_texture = cpLoadTexture("textures/in_game_frame.png");

   if (!rsu_24_font || !hit_paddle_sound || !hit_brick_sound || !hit_top_sound || !end_sound ||
       !paddle_texture || !ball_texture || !brick_texture || !in_game_bg_texture ||
       !in_game_frame_texture)
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

    showInGameScreen();

    cpCleanUp();
    return 0;
}
