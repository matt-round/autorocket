//
// Created by Matthew Round on 05/03/2020.
//

#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_world.h>
#include "PhysicsGround.h"

PhysicsGround::PhysicsGround(b2World &world, float width, float yPos)
        : m_world{world},
          m_width{width},
          m_height{1}, // set the height (you shouldn't need to change this).
          m_yPos{yPos} {

    // compensate for height
    m_yPos += m_height;

    b2BodyDef groundBodyDef;
    constexpr float groundBoxX{0};
    const float groundBoxY{m_yPos};

    b2Body *groundBody;
    groundBodyDef.position.Set(groundBoxX, groundBoxY-m_height);
    groundBody = m_world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(m_width, m_height);
    constexpr float groundDensity{0.0f};
    groundBody->CreateFixture(&groundBox, groundDensity);

}

float PhysicsGround::getWidth() {
    return m_width;
}

float PhysicsGround::getYPos() {
    return m_yPos;
}