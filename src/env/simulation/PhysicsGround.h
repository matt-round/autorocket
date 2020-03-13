//
// Created by Matthew Round on 05/03/2020.
//

#ifndef RSLR_PHYSICSGROUND_H
#define RSLR_PHYSICSGROUND_H

#include <b2_world.h>

class PhysicsGround {
public:
    PhysicsGround(b2World &world, float width, float yPos);
    float getWidth();
    float getYPos();

private:
    b2World &m_world;
    float m_width;
    float m_yPos;
    float m_height;
};


#endif //RSLR_PHYSICSGROUND_H
