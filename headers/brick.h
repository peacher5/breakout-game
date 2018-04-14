#ifndef BRICK_H
#define BRICK_H

#include "object.h"

typedef enum {NoEffect, BallsSpread, BallSpeedIncrease, MissileAmmo} BrickType;

class Brick: public Object {
    protected:
        int durability_, score_;
        Texture crack_texture_;
        BrickType type_;
    public:
        Brick();

        void setScore(int score);
        void setDurability(int durability);
        void decreaseDurability();
        void setCrackTexture(Texture crack_texture);
        void setBrickType(BrickType type);

        int getScore();
        int getDurability();
        BrickType getBrickType();
};

#endif // BRICK_H