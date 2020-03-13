//
// Created by Matthew Round on 05/03/2020.
//

#ifndef RSLR_PHYSICSMAPPINGGRAPHICSITEM_H
#define RSLR_PHYSICSMAPPINGGRAPHICSITEM_H


#include <QGraphicsItem>
#include <vector>
#include <b2_math.h>

class PhysicsMappingGraphicsItem : public QGraphicsItem {
public:
    void loadBody(const std::vector<b2Vec2>&body);
    void loadBody(const std::vector<b2Vec2>&body, int scalingFactor);

protected:
    std::vector<QPointF> m_body;
    int m_MPR;
};


#endif //RSLR_PHYSICSMAPPINGGRAPHICSITEM_H
