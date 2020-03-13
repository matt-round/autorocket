//
// Created by Matthew Round on 11/03/2020.
//

#ifndef RSLR_DATASTRUCTS_H
#define RSLR_DATASTRUCTS_H

namespace datastructs {
    struct state {
        float yPosition;
        float angle;
    };
    struct discreteState {
        int yPosition;
        int angle;
    };
}

#endif //RSLR_DATASTRUCTS_H
