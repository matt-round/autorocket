//
// Created by Matthew Round on 05/03/2020.
//

#include <b2_math.h>
#include "PhysicsMappingGraphicsItem.h"

void PhysicsMappingGraphicsItem::loadBody(const std::vector<b2Vec2> &body) {
    for(auto &vector : body) {
        m_body.emplace_back(QPointF{vector.x, vector.y});
    }
}

void PhysicsMappingGraphicsItem::loadBody(const std::vector<b2Vec2> &body, int scalingFactor) {
    for(auto &vector : body) {
        m_body.emplace_back(QPointF{(vector.x*scalingFactor)*-1, (vector.y*scalingFactor)*-1});
    }
    m_MPR = scalingFactor;
}