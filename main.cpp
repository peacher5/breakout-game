#include <iostream>

#include "headers/cp_functions.h"
#include "headers/object.h"
#include "headers/ball.h"
#include "headers/brick.h"

#define WINDOW_TITLE  "Breakout"
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 700

using namespace std;

Font rsu_24_font;
Sound hit_paddle_sound, hit_brick_sound, hit_top_sound, end_sound;
Texture paddle_texture, ball_texture, brick_texture;
Texture in_game_bg_texture, in_game_frame_texture;

Event event;

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

Object paddle(0, 0, 124, 18);
Ball ball(0, 0, 20, 20, 0, 0);
Brick bricks[100];
int n_bricks;

void drawInGameTexture() {
    // In-game Background
    cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, in_game_bg_texture);
    // In-game Frame
    cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, in_game_frame_texture);
    // Paddle
    paddle.drawTexture(paddle_texture);
    // Ball
    ball.drawTexture(ball_texture);
    // Bricks
    for (int i = 0; i < n_bricks; i++) {
        if (!bricks[i].isDestroy())
            bricks[i].drawTexture(brick_texture);
    }
}

void showInGameScreen() {
    // Init paddle
    paddle.setX(WINDOW_WIDTH / 2 - paddle.getWidth() / 2);
    paddle.setY(WINDOW_HEIGHT - 80);

    // Init ball
    ball.setX(WINDOW_WIDTH / 2 - ball.getWidth() / 2);
    ball.setY(paddle.getY() - ball.getHeight() - 1);

    // Init bricks for level 1
    n_bricks = 96;
    for (int i = 0, x = 100, y = 120; i < n_bricks; i++) {
            bricks[i].setX(x);
            bricks[i].setY(y);
            bricks[i].setWidth(50);
            bricks[i].setHeight(25);
        if (x > WINDOW_WIDTH - 200)
            x = 100, y += 25;
        else
            x += 50;
    }

    while (true) {
        cpClearScreen();
        drawInGameTexture();
        // Update Screen
        cpSwapBuffers();
        // Handle events
        while (cbPollEvent(&event)) {
            if (event.type == QUIT) {
                return;
            }
        }
        cpDelay(10);
    }
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
