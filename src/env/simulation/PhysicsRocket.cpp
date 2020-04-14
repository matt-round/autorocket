//
// Created by Matthew Round on 05/03/2020.
//

#include "PhysicsRocket.h"
#include <vector>
#include <iostream>
#include <cmath>

PhysicsRocket::PhysicsRocket(b2World& world) : m_world{world} {
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.position.Set(0, 0);
    m_body = m_world.CreateBody(&m_bodyDef);
    b2Vec2 vertices[5];
    vertices[0].Set(0.0, 6.0);
    vertices[1].Set(-0.5, 4.0);
    vertices[2].Set(-0.5, 0.0);
    vertices[3].Set(0.5, 0.0);
    vertices[4].Set(0.5, 4.0);

    m_dynamicBox.Set(vertices, 5);

    m_fixtureDef.shape = &m_dynamicBox;
    m_fixtureDef.density = 1.0f;
    m_fixtureDef.friction = 0.5f;
    m_fixtureDef.restitution = 0.3f;

    m_body->CreateFixture(&m_fixtureDef);
}

std::vector<b2Vec2> PhysicsRocket::getVertices() {
    return std::vector<b2Vec2>(std::begin(m_dynamicBox.m_vertices),
                               std::end(m_dynamicBox.m_vertices));
}

b2Vec2 PhysicsRocket::getPos() {
    return m_body->GetPosition();
}

float PhysicsRocket::getAngle() {
    return m_body->GetAngle();
}

float PhysicsRocket::getNormalisedAngle() {
    return std::fmod(m_body->GetAngle(), static_cast<float>(2*M_PI));
}

float PhysicsRocket::getLinearVelocity() {
    return m_body->GetLinearVelocity().y;
}


float PhysicsRocket::getAngularVelocity() {
    return m_body->GetAngularVelocity();
}

void PhysicsRocket::setAngularVelocity(float v) {
    m_body->SetAngularVelocity(v);
}

void PhysicsRocket::applyWindForce(float windSpeed) {
    m_body->ApplyForceToCenter(b2Vec2(windSpeed,0), false);
}

void PhysicsRocket::applyForceLeft() {
    m_body -> ApplyForce(b2Vec2(-20,0), m_body->GetWorldCenter()+b2Vec2(0,3), true);
}

void PhysicsRocket::applyForceRight() {
    m_body -> ApplyForce(b2Vec2(20,0), m_body->GetWorldCenter()+b2Vec2(0,3), true);
}

void PhysicsRocket::applyThrust() {
    float magnitude = 100;
    b2Vec2 forceDirection = m_body->GetWorldVector( b2Vec2(0,1) );
    forceDirection = magnitude * forceDirection;
    m_body->ApplyForce(forceDirection, m_body->GetPosition(), true);
}

bool PhysicsRocket::isAwake() {
    return m_body->IsAwake();
}

void PhysicsRocket::reset() {
    m_body->SetLinearVelocity(b2Vec2(0,-1));
    m_body->SetAngularVelocity(0.0f);
    float maxRandValue = 60.0f;
    float randomAngleRadians = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/maxRandValue));
    float initRocketAngleDegrees = randomAngleRadians*(M_PI/180);
    initRocketAngleDegrees = (rand() > RAND_MAX/2) ? initRocketAngleDegrees : initRocketAngleDegrees * -1;
    m_body->SetTransform(b2Vec2(-35,-10), initRocketAngleDegrees);
}