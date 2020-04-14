//
// Created by Matthew Round on 11/03/2020.
//

#ifndef RSLR_DATASTRUCTS_H
#define RSLR_DATASTRUCTS_H

namespace datastructs {
    struct state {
        float xPosition;
        float yPosition;
        float angle;
        float linearVelocity;
        float angularVelocity;
    };
    struct discreteState {
        int xPosition;
        int yPosition;
        int angle;
        int linearVelocity;
        int angularVelocity;
    };
}

#endif //RSLR_DATASTRUCTS_H
