//
// Created by Matthew Round on 04/03/2020.
//

#include "Rocket.h"
#include <QBrush>
#include <QPainter>
#include <iostream>

Rocket::Rocket() {
}

QRectF Rocket::boundingRect() const {
    return QRect(-200, -500, 500, 500);
}

void Rocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QBrush brush(Qt::red);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);
    painter->drawPolygon(m_body.data(), 5);
}

void Rocket::advance(int phase) {
    if(!phase) return;
}

void Rocket::moveRocket(std::array<float, 2> position, int MPR) {
    enum {
        x = 0,
        y = 1
    };
    setPos(-1*(position.at(x)*MPR), -1*(position.at(y)*MPR));
}

void Rocket::setAngle(float angle, int MPR) {
    setRotation((angle * 360.0) / (2 * M_PI));
}