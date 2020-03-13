//
// Created by Matthew Round on 06/03/2020.
//

#ifndef RSLR_MOVEROCKETEVENT_H
#define RSLR_MOVEROCKETEVENT_H


#include <QEvent>
#include <array>

class MoveRocketEvent : public QEvent {
public:
    explicit MoveRocketEvent(QEvent::Type type);
    std::array<float, 2> position;
    float angle;
};


#endif //RSLR_MOVEROCKETEVENT_H
