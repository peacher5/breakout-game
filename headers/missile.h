#ifndef MISSILE_H
#define MISSILE_H

#include "object.h"

class Missile: public Object {
    protected:
        bool is_visible_;
    public:
        Missile();

        void setVisible(bool toggle);

        int isVisible();
};

#endif // MISSILE_H