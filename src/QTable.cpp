//
// Created by Matthew Round on 11/03/2020.
//

#include <iostream>
#include "QTable.h"

QTable::QTable(int x, int y, int z) :
    m_width{x},
    m_height{y},
    m_depth{z} {
    qTable.resize(x*y*z);
}

float& QTable::get(int x, int y, int z) {
    try {
        return qTable.at(x + m_width * (y + m_height * z));
    } catch (const std::out_of_range& oor) {
        return qTable.at((m_width-1) + m_width * (y + m_height * z));
    }
}

void QTable::update(int x, int y, int z, float value) {
    qTable[x + m_width * (y + m_height * z)] = value;
}

std::vector<float> QTable::get(int x, int y) {
    std::vector<float> row;
    for(int i = 0; i < m_depth; ++i) {
        row.push_back(get(x, y, i));
    }
    return row;
}

float QTable::maxFutureQ(int x, int y) {
    float max {get(x, y, 0)};
    for(int i = 1; i < m_depth; ++i) {
        float v {get(x, y, i)};
        if(v > max) max = v;
    }
    return max;
}

void QTable::randomFill() {
    for(auto &v : qTable) {
        v = randomFloat(-6.0f, 0);
    }
}

float QTable::randomFloat(float min, float max) {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

