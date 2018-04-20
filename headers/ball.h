#ifndef BALL_H
#define BALL_H

#include "object.h"

class Ball: public Object {
    protected:
        bool isOnScreen_;
    public:
        Ball();
        Ball(float width, float height);

        void invertVelX();
        void invertVelY();
        void setIsOnScreen(bool isOnScreen);

        bool isOnScreen();
};

#endif // BALL_H