//
// Created by Matthew Round on 05/03/2020.
//

#ifndef RSLR_SIMULATION_H
#define RSLR_SIMULATION_H

#include <b2_math.h>
#include <b2_world.h>
#include <QApplication>
#include <thread>
#include "PhysicsGround.h"
#include "PhysicsRocket.h"
//#include "../gui/MainWindow.h"

class MainWindow;

class Simulation {
public:
    Simulation(float gravity, bool wind);
    int getWorldWidth();
    int getWorldHeight();
    PhysicsGround getGround();
    PhysicsRocket getRocket();
    std::thread* run(QApplication &app, MainWindow &w, bool &exitFlag);
    void reset();
    void step();
    void updateGraphics(QApplication &app, MainWindow &w, float timeStep);

private:
    b2Vec2 m_gravity;
    b2World m_world;
    int m_worldHeight;
    int m_worldWidth;
    PhysicsGround m_ground;
    PhysicsRocket m_rocket;
    bool m_wind;
    void m_simulation(QApplication &app, MainWindow &w, bool &exitFlag);
    int m_windSpeed;
    int randomWindSpeed(int min, int max);
};


#endif //RSLR_SIMULATION_H
