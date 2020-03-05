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
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget) override;
protected:
    void advance(int phase) override;
};


#endif //RSLR_ROCKET_H
