#ifndef BRICK_H
#define BRICK_H

#include "object.h"

class Brick: public Object {
    private:
        int durability_, score_;
    protected:
        Brick(int durability);
    public:
        Brick();

        void setScore(int score);
        virtual void decreaseDurability();

        int getScore();
        int getDurability();
};

#endif // BRICK_H