//
// Created by Matthew Round on 05/03/2020.
//

#ifndef RSLR_PHYSICSROCKET_H
#define RSLR_PHYSICSROCKET_H


#include <b2_world.h>
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_math.h>

class PhysicsRocket {

public:
    PhysicsRocket(b2World &world);
    std::vector<b2Vec2> getVertices();
    b2Vec2 getPos();
    float getAngle();
    float getNormalisedAngle();
    void applyWindForce(float windSpeed);
    void applyForceLeft();
    void applyForceRight();
    void applyThrust();
    bool isAwake();
    void reset();
    float getAngularVelocity();
    void setAngularVelocity(float v);

private:
    b2World& m_world;
    b2Body* m_body;
    b2BodyDef m_bodyDef;
    b2PolygonShape m_dynamicBox;
    b2FixtureDef m_fixtureDef;
};


#endif //RSLR_PHYSICSROCKET_H
