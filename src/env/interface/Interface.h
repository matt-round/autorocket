//
// Created by Matthew Round on 08/03/2020.
//

#ifndef RSLR_INTERFACE_H
#define RSLR_INTERFACE_H

#include "../simulation/Simulation.h"
#include "../../datastructs.h"

class Interface {
public:
    explicit Interface(Simulation& sim, float discreteOSSize);

    void moveRocketRight();
    void moveRocketLeft();
    void thrust();
    void reset();
    datastructs::state state();
    datastructs::discreteState discreteState();
    float reward();
    std::tuple<float, float, float> observationSpaceHigh();
    std::tuple<float, float, float> observationSpaceLow();
    int actionSpaceCount();
    void step(int action);


private:
    Simulation& m_sim;
    const std::array<float, 3> m_discreteOSWinSize;
};


#endif //RSLR_INTERFACE_H
