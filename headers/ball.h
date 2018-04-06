#ifndef BALL_H
#define BALL_H

#include "object.h"

class Ball: public Object {
    protected:
        float velX_, velY_;
        bool isOnScreen_;
    public:
        Ball(float x, float y, float width, float height, float velX, float velY);

        void setVelX(float velX);
        void setVelY(float velY);
        void setIsOnScreen(bool isOnScreen);

        float getVelX();
        float getVelY();

        bool isOnScreen();
};

#endif // BALL_H