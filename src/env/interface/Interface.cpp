//
// Created by Matthew Round on 08/03/2020.
//

#include <iostream>
#include "Interface.h"

Interface::Interface(Simulation &sim, float discreteOSSize) :
        m_sim(sim),
        m_discreteOSWinSize{
                // x position
                (std::get<0>(observationSpaceHigh()) - std::get<0>(observationSpaceLow())) / discreteOSSize,
                // y pos
                (std::get<1>(observationSpaceHigh()) - std::get<1>(observationSpaceLow())) / discreteOSSize,
                // angle
                (std::get<2>(observationSpaceHigh()) - std::get<2>(observationSpaceLow())) / discreteOSSize,
                // linear velocity
                (std::get<3>(observationSpaceHigh()) - std::get<3>(observationSpaceLow())) / discreteOSSize,
                // angular velocity
                (std::get<4>(observationSpaceHigh()) - std::get<4>(observationSpaceLow())) / discreteOSSize
        },
        m_discreteOSSize{discreteOSSize} {


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
    float posX {rocket.getPos().x};
    float posY {rocket.getPos().y};
    float angle {rocket.getNormalisedAngle()};
    float linearVelocity {rocket.getLinearVelocity()};
    float angularVelocity {rocket.getAngularVelocity()};

    return datastructs::state {posX, posY, angle, linearVelocity, angularVelocity};
}

datastructs::discreteState Interface::discreteState() {
    datastructs::state oldState = state();

    int xPosNormalised {
            static_cast<int>((oldState.xPosition - std::get<0>(observationSpaceLow())) / m_discreteOSWinSize[0])
    };
    int yPosNormalised {
        static_cast<int>((oldState.yPosition - std::get<1>(observationSpaceLow())) / m_discreteOSWinSize[1])
    };
    int angleNormalised {
            static_cast<int>((oldState.angle - std::get<2>(observationSpaceLow())) / m_discreteOSWinSize[2])
    };
    int linearVelocityNormalised {
            static_cast<int>((oldState.linearVelocity - std::get<3>(observationSpaceLow())) / m_discreteOSWinSize[3])
    };
    int angularVelocityNormalised {
            static_cast<int>((oldState.angularVelocity - std::get<4>(observationSpaceLow())) / m_discreteOSWinSize[4])
    };

    if(xPosNormalised >= m_discreteOSSize) {
        xPosNormalised = m_discreteOSSize-1;
    } else if(xPosNormalised < 0) {
        xPosNormalised = 0;
    }

    if(yPosNormalised >= m_discreteOSSize) {
        yPosNormalised = m_discreteOSSize-1;
    } else if(yPosNormalised < 0) {
        yPosNormalised = 0;
    }

    if(angleNormalised >= m_discreteOSSize) {
        angleNormalised = m_discreteOSSize-1;
    } else if (angleNormalised < 0) {
        angleNormalised = 0;
    }

    if(linearVelocityNormalised >= m_discreteOSSize) {
        linearVelocityNormalised = m_discreteOSSize-1;
    } else if (linearVelocityNormalised < 0) {
        linearVelocityNormalised = 0;
    }

    if(angularVelocityNormalised >= m_discreteOSSize) {
        angularVelocityNormalised = m_discreteOSSize-1;
    } else if (angularVelocityNormalised < 0) {
        angularVelocityNormalised = 0;
    }

    return datastructs::discreteState {
        xPosNormalised, yPosNormalised, angleNormalised, linearVelocityNormalised, angularVelocityNormalised
    };
}

float Interface::reward() {
    PhysicsRocket rocket {m_sim.getRocket()};
    const float &posX {rocket.getPos().x};
    const float &posY {rocket.getPos().y};
    const float &angle {rocket.getNormalisedAngle()};
    float reward;
    if(!rocket.isAwake() && posY < -68 && posY > -69 && angle < 0.01 && angle > -0.01) {
        reward = 100.0f;
    } else if(posY >= 0 || posY < -70 || posX >= 0 || posX < -70) {
        reward = -20;
    }
    else {
        reward = -1 - abs(angle) - abs((-68-(posY))/10);
    }
    return reward;
}

std::tuple<float, float, float, float, float> Interface::observationSpaceHigh() {
    return std::make_tuple(0.0f, 0.0f, M_PI*2, 70.0f, 10.0f);
}

std::tuple<float, float, float, float, float> Interface::observationSpaceLow() {
    return std::make_tuple(-70.0f, -70.0f, -(M_PI*2), -70.0f, -10.0f);
}

int Interface::actionSpaceCount() {
    return 4;
}

void Interface::step(int action) {
    switch(action) {
        case 1:
            moveRocketRight();
            break;
        case 2:
            moveRocketLeft();
        case 3:
            thrust();
        default:
            break;
    }
    m_sim.step();
}