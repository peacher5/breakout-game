#include <iostream>
#include <cmath>

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

// Global var for In-game Scene
Object paddle(0, 0, 124, 18);
Ball ball(0, 0, 20, 20, 0, 0);
Brick bricks[100];
int n_bricks;
bool is_game_start;

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

void setMouseVisible(bool toggle) {
    // Show/hide cursor in the window.
    SDL_ShowCursor(toggle);
    // Confined cursor to the window.
    if (toggle)
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    else
        SDL_WM_GrabInput(SDL_GRAB_ON);
}

void setMouseX(int mouse_x) {
    // Set mouse x position (y position is not used when hiding cursor)
    SDL_WarpMouse(mouse_x, 0);
}

int getMouseX() {
    int mouse_x;
    // Get only mouse x position
    SDL_GetMouseState(&mouse_x, NULL);
    return mouse_x;
}

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
    // Set ball speed & start angle (0 degree = go up straight)
    float ball_vel = 7, bounce_angle = 0;
    // Set max ball angle when collide w/ paddle = 70 degee angle
    const float MAX_BOUNCE_ANGLE = 7 * M_PI / 18;

    // Hide mouse cursor
    setMouseVisible(false);

    // Init paddle position
    paddle.setX(getMouseX() - paddle.getWidth() / 2);
    paddle.setY(WINDOW_HEIGHT - 80);

    // Prevent paddle get out of window (In-game Frame side border width = 10px)
    if (paddle.getX() < 10)
        paddle.setX(10);
    else if (paddle.getX() + paddle.getWidth() > WINDOW_WIDTH - 10)
        paddle.setX(WINDOW_WIDTH - paddle.getWidth() - 10);

    // Init ball position
    ball.setX(paddle.getX() + paddle.getWidth() / 2 - ball.getWidth() / 2);
    ball.setY(paddle.getY() - ball.getHeight() - 1);

    // Init ball velocity in x/y pos
    ball.setVelX(ball_vel * sin(bounce_angle));
    ball.setVelY(-ball_vel * cos(bounce_angle));

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
            // User released ESC key
            if (event.type == KEYUP && event.key.keysym.sym == SDLK_ESCAPE) {
                return;
            }
            // Start the game (release ball) when user press left click
            if (!is_game_start && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                is_game_start = true;
                break;
            }
        }

        // Set paddle position related to mouse position
        paddle.setX(getMouseX() - paddle.getWidth() / 2);

        // Prevent paddle get out of window (In-game Frame side border width = 10px)
        if (paddle.getX() < 10)
            paddle.setX(10);
        else if (paddle.getX() + paddle.getWidth() > WINDOW_WIDTH - 10)
            paddle.setX(WINDOW_WIDTH - paddle.getWidth() - 10);

        if (!is_game_start)
            // Set ball position to center of paddle
            ball.setX(paddle.getX() + paddle.getWidth() / 2 - ball.getWidth() / 2);
        else
            // Set ball position related to ball x/y velocity
            ball.move();

        // Prevent ball get out of window (In-game Frame side border width = 9px)
        if (ball.getX() < 10) {
            ball.setX(10);
            ball.invertVelX();
        }
        if (ball.getX() + ball.getWidth() > WINDOW_WIDTH - 10) {
            ball.setX(WINDOW_WIDTH - ball.getWidth() - 10);
            ball.invertVelX();
        }
        // In-game Frame header height = 63px
        if (ball.getY() < 64) {
            cpPlaySound(hit_top_sound);
            ball.setY(64);
            ball.invertVelY();
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
