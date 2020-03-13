//
// Created by Matthew Round on 04/03/2020.
//

#ifndef RSLR_ROCKET_H
#define RSLR_ROCKET_H

#include <QGraphicsItem>
#include <QRectF>
#include "PhysicsMappingGraphicsItem.h"


class Rocket : public PhysicsMappingGraphicsItem {
public:
    Rocket();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget) override;
    void moveRocket(std::array<float, 2> position, int MPR);
    void setAngle(float angle, int MPR);

protected:
    void advance(int phase) override;
};


#endif //RSLR_ROCKET_H
