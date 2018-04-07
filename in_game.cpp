#include <cmath>
#include "headers/global.h"
#include <iostream>

// Global shared resources from main
extern Font rsu_24_font, rsu_30_font;
extern Sound hit_paddle_sound, hit_brick_sound, hit_top_sound, end_sound;
extern Texture paddle_texture, ball_texture, brick_texture, in_game_bg_texture, in_game_frame_texture;

// Global vars for In-game Scene
Object paddle(124, 18);
Ball ball(20, 20);
Brick bricks[100];
typedef enum {NoCollide, CollideTop, CollideBottom, CollideLeft, CollideRight} CollisionSide;
int n_bricks, score;
bool is_game_start;

/*  Collision Detection between two objects a and b
    Return collision side of objects a  */
CollisionSide collide(Object a, Object b) {
    float w = (a.getWidth() + b.getWidth()) / 2;
    float h = (a.getHeight() + b.getHeight()) / 2;
    float dx = (a.getX() + a.getWidth() / 2) - (b.getX() + b.getWidth() / 2);
    float dy = (a.getY() + a.getHeight() / 2) - (b.getY() + b.getHeight() / 2);

    // Collision detect
    if (fabs(dx) <= w && fabs(dy) <= h) {
        float wy = w * dy;
        float hx = h * dx;

        if (wy > hx) {
            if (wy > -hx)
                return CollideTop;
            else
                return CollideRight;
        } else {
            if (wy > -hx)
                return CollideLeft;
            else
                return CollideBottom;
        }
    }
    // No collision detect
    return NoCollide;
}

void drawScoreText(int score) {
    char scoreDigit[2];
    for (int i = 0, x = 150; i < 5; i++, x -= 27) {
        sprintf(scoreDigit, "%d", score % 10);
        cpDrawText(255, 255, 255, 216, x, 43, scoreDigit, rsu_30_font, true);
        score /= 10;
    }
}

void drawInGameTexture() {
    // In-game Background
    cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, in_game_bg_texture);
    // Paddle
    paddle.drawTexture(paddle_texture);
    // Ball
    ball.drawTexture(ball_texture);
    // Bricks
    for (int i = 0; i < n_bricks; i++) {
        // if durability != 0 then draw a brick
        if (bricks[i].getDurability())
            bricks[i].drawTexture(brick_texture);
    }
    // In-game Frame
    cpDrawTexture(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, in_game_frame_texture);
    // Score
    drawScoreText(score);
}

void showInGameScreen() {
    // For store event from PollEvent function
    Event event;
    // Set ball speed & start angle (0 degree = go up straight)
    float ball_vel = 7, bounce_angle = 0;
    // Set max ball angle when collide w/ paddle = 70 degee angle
    const float MAX_BOUNCE_ANGLE = 7 * M_PI / 18;
    // Temp vars for calculate angle
    float relative_intersect, normalized_relative_intersect;
    // Store collide side
    int side;

    // Hide mouse cursor
    setMouseVisible(false);

    // Init paddle position
    paddle.setX(getMouseX() - paddle.getWidth() / 2);
    paddle.setY(WINDOW_HEIGHT - 80);

    // Prevent paddle get out of window (In-game Frame side border width = 9px)
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

        for (int i = 0; i < n_bricks; i++) {
            // When ball hit a brick
            if (bricks[i].getDurability() && (side = collide(bricks[i], ball))) {
                // Play sound
                cpPlaySound(hit_brick_sound);

                // Decrease durability by 1
                bricks[i].decreaseDurability();

                // + Score
                score += 5;

                // Prevent ball get into brick
                switch (side) {
                    case CollideTop:
                        ball.setY(bricks[i].getY() - ball.getHeight() - 1);
                        // Set ball to go up only
                        ball.setVelY(-fabs(ball.getVelY()));
                        break;
                    case CollideBottom:
                        ball.setY(bricks[i].getY() + bricks[i].getHeight() + 1);
                        // Set ball to go down only
                        ball.setVelY(fabs(ball.getVelY()));
                        break;
                    case CollideLeft:
                        ball.setX(bricks[i].getX() - ball.getWidth() - 1);
                        // Set ball to go only left side
                        ball.setVelX(-fabs(ball.getVelX()));
                        break;
                    case CollideRight:
                        ball.setX(bricks[i].getX() + bricks[i].getWidth() + 1);
                        // Set ball to go only right side
                        ball.setVelX(fabs(ball.getVelX()));
                }
            }
        }

        // When ball hit paddle
        if ((side = collide(paddle, ball))) {
            cpPlaySound(hit_paddle_sound);

            // Set new ball angle related to collide position on paddle
            relative_intersect = (ball.getX() + ball.getWidth() / 2) - (paddle.getX() + paddle.getWidth() / 2);
            normalized_relative_intersect = relative_intersect / (paddle.getWidth() / 2);
            bounce_angle = normalized_relative_intersect * MAX_BOUNCE_ANGLE;

            ball.setVelX(ball_vel * sin(bounce_angle));
            ball.setVelY(-ball_vel * cos(bounce_angle));

            // Prevent ball get into paddle
            switch (side) {
                case CollideTop:
                    ball.setY(paddle.getY() - ball.getHeight() - 1);
                    break;
                case CollideLeft:
                    ball.setX(paddle.getX() - ball.getWidth() - 1);
                    // Set ball to go only left side
                    ball.setVelX(-fabs(ball.getVelX()));
                    break;
                case CollideRight:
                    ball.setX(paddle.getX() + paddle.getWidth() + 1);
                    // Set ball to go only right side
                    ball.setVelX(fabs(ball.getVelX()));
            }
        }

        cpDelay(10);
    }
}