//
// Created by Matthew Round on 05/03/2020.
//

#include "Simulation.h"
#include "PhysicsGround.h"
#include "../gui/MainWindow.h"
#include "../gui/MoveRocketEvent.h"
#include <b2_world.h>
#include <thread>
#include <QApplication>
#include <iostream>
#include <QEvent>
#include <array>
#include <chrono>
#include <ctime>
#include <cmath>

Simulation::Simulation(const float gravity, const bool wind)
        : m_gravity{b2Vec2{0.0f, gravity}},
          m_wind{wind},
          m_world{m_gravity},
          m_worldWidth{70},
          m_worldHeight{70},
          m_ground{m_world, static_cast<float>(m_worldWidth*10), -static_cast<float>(m_worldHeight)},
          m_rocket{m_world},
          m_windSpeed{0} {

    srand((int)time(0));

    if(m_wind) {
        m_windSpeed = randomWindSpeed(-15, 15);
    }

}

int Simulation::randomWindSpeed(int min, int max) {
    const int windSpeed {(rand() % (max-min+1)) + min};
    return windSpeed; // random number : min <= r <=max
}

int Simulation::getWorldWidth() {
    return m_worldWidth;
}

int Simulation::getWorldHeight() {
    return m_worldWidth;
}

PhysicsGround Simulation::getGround() {
    return m_ground;
}

PhysicsRocket Simulation::getRocket() {
    return m_rocket;
}

void Simulation::step() {
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    if(m_wind) {
        m_rocket.applyWindForce(m_windSpeed);
    }
    m_world.Step(timeStep, velocityIterations, positionIterations);
    float maxV {10.0f};
    float minV {-10.0f};
    if(m_rocket.getAngularVelocity() > maxV) {
        m_rocket.setAngularVelocity(maxV);
    } else if(m_rocket.getAngularVelocity() < minV) {
        m_rocket.setAngularVelocity(minV);
    }
}

std::thread* Simulation::run(QApplication &app, MainWindow &w, bool &exitFlag) {
    auto* threadObj = new std::thread(&Simulation::m_simulation, this, std::ref(app), std::ref(w), std::ref(exitFlag));
    return threadObj;
}

void Simulation::updateGraphics(QApplication &app, MainWindow &w, float timeStep) {
    MainWindow* mainWindowPtr {&w};
    // update graphics
    auto* moveRocketEvent = new MoveRocketEvent(QEvent::User);

    moveRocketEvent->position = std::array<float, 2>{m_rocket.getPos().x, m_rocket.getPos().y};
    // normalisedAngle needed because angle is unbounded.
    float normalisedAngle {m_rocket.getNormalisedAngle()};
    moveRocketEvent->angle = normalisedAngle;
    app.postEvent(mainWindowPtr, reinterpret_cast<QEvent*>(moveRocketEvent));
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(timeStep*1000)));
}

void Simulation::m_simulation(QApplication &app, MainWindow &w, bool &exitFlag) {
    MainWindow* mainWindowPtr {&w};
    m_rocket.reset();
    while(!exitFlag) {
        auto start = std::chrono::high_resolution_clock::now();
        float timeStep = 1.0f / 60.0f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        if(m_wind) {
            m_rocket.applyWindForce(m_windSpeed);
        }
        m_world.Step(timeStep, velocityIterations, positionIterations);

        // update graphics
        auto* moveRocketEvent = new MoveRocketEvent(QEvent::User);

        moveRocketEvent->position = std::array<float, 2>{m_rocket.getPos().x, m_rocket.getPos().y};
        // normalisedAngle needed because angle is unbounded.
        float normalisedAngle {m_rocket.getNormalisedAngle()};
        moveRocketEvent->angle = normalisedAngle;
        //std::cout << "Angle: " << normalisedAngle << " YPos: " << m_rocket.getPos().y << " awake: " << m_rocket.isAwake() << '\n';
        app.postEvent(mainWindowPtr, reinterpret_cast<QEvent*>(moveRocketEvent));
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((timeStep*1000)-(elapsed.count()*1000))));
    }
}

void Simulation::reset() {
    m_windSpeed = randomWindSpeed(-15, 15);
    m_rocket.reset();
}