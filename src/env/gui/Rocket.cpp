//
// Created by Matthew Round on 04/03/2020.
//

#include "Rocket.h"
#include <QBrush>
#include <QPainter>

QRectF Rocket::boundingRect() const {
    return QRect(-200, -200, 500, 500);
}

void Rocket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QBrush brush(Qt::red);
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen);

    QPointF points[10] = {
            QPointF(0.0, -6.0),
            QPointF(0.5, -4.0),
            QPointF(0.5, -1.0),
            QPointF(0.7, 0.0),
            QPointF(0.5, 0.0),
            QPointF(0.0, -1.0),
            QPointF(-0.5, 0.0),
            QPointF(-0.7, 0.0),
            QPointF(-0.5, -1.0),
            QPointF(-0.5, -4.0)
    };

    for(auto &point : points) {
        point.setX(point.x() * 300);
        point.setY(point.y() * 300);
    }
    painter->drawPolygon(points, 10);
}

void Rocket::advance(int phase) {
    if(!phase) return;
}