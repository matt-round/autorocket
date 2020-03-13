//
// Created by Matthew Round on 08/03/2020.
//

#include <iostream>
#include "Interface.h"

Interface::Interface(Simulation &sim, float discreteOSSize) :
        m_sim(sim),
        m_discreteOSWinSize{
                // position
                (std::get<0>(observationSpaceHigh()) - std::get<0>(observationSpaceLow())) / discreteOSSize,
                // angle
                (std::get<1>(observationSpaceHigh()) - std::get<1>(observationSpaceLow())) / discreteOSSize
        } {


}

void Interface::moveRocketLeft() {
    m_sim.getRocket().applyForceRight();
}

void Interface::moveRocketRight() {
    m_sim.getRocket().applyForceLeft();
}

void Interface::thrust() {
    m_sim.getRocket().applyThrust();
}

void Interface::reset() {
    m_sim.reset();
}

datastructs::state Interface::state() {
    PhysicsRocket rocket {m_sim.getRocket()};
    const float &posY {rocket.getPos().y};
    const float &angle {rocket.getNormalisedAngle()};
    return datastructs::state {posY, angle};
}

datastructs::discreteState Interface::discreteState() {
    datastructs::state oldState = state();

    int yPosNormalised {
        static_cast<int>((oldState.yPosition - std::get<0>(observationSpaceLow())) / m_discreteOSWinSize[0])
    };
    int angleNormalised {
            static_cast<int>((oldState.angle - std::get<1>(observationSpaceLow())) / m_discreteOSWinSize[1])
    };
    return datastructs::discreteState {yPosNormalised, angleNormalised};
}

float Interface::reward() {
    PhysicsRocket rocket {m_sim.getRocket()};
    const float &posY {rocket.getPos().y};
    const float &angle {rocket.getNormalisedAngle()};
    float reward;
    if(!rocket.isAwake() && posY < -68 && posY > -69 && angle < 0.01 && angle > -0.01) {
        reward = 10.0f;
    } else {
        reward = -1 - abs(angle);
    }
    return reward;
}

std::tuple<float, float> Interface::observationSpaceHigh() {
    return std::make_tuple(0.0f, M_PI*2);
}

std::tuple<float, float> Interface::observationSpaceLow() {
    return std::make_tuple(-70.0f, -(M_PI*2));
}

int Interface::actionSpaceCount() {
    return 3;
}

void Interface::step(int action) {
    switch(action) {
        case 1:
            moveRocketRight();
            break;
        case 2:
            moveRocketLeft();
        default:
            break;
    }
    m_sim.step();
}