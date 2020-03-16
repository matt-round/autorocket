//
// Created by Matthew Round on 11/03/2020.
//

#include <iostream>
#include <utility>
#include "QTable.h"

QTable::QTable(std::vector<int> qTableDef) :
    m_tableDef{std::move(qTableDef)} {
    int tableSize {1};
    for(int dimensionSize : m_tableDef) {
        tableSize *= dimensionSize;
    }
    qTable.resize(tableSize);
}

int QTable::m_elementPosition(std::vector<int> position) {
    int elementPos {position.at(1) + m_tableDef.at(1) * position.at(0)};
    for(int i {2}; i < position.size(); ++i) {
        elementPos = position.at(i) + m_tableDef.at(i) * elementPos;
    }
    return elementPos;
}

float& QTable::get(std::vector<int> position) {
    return qTable.at(m_elementPosition(std::move(position)));
}

void QTable::update(std::vector<int> position, float value) {
    qTable[m_elementPosition(std::move(position))] = value;
}

std::vector<float> QTable::getRow(std::vector<int> position) {
    position.push_back(0); // set position in last dimension to 0.
    int firstElementPositionInMemory {m_elementPosition(position)};
    std::vector<float> row;
    for(int i = 0; i < m_tableDef.back(); ++i) {
        row.push_back(qTable.at(firstElementPositionInMemory+i));
    }
    return row;
}

float QTable::maxFutureQ(std::vector<int> position) {
    position.push_back(0); // set position in last dimension to 0.
    int firstElementPositionInMemory {m_elementPosition(position)};
    float max {qTable.at(firstElementPositionInMemory)};
    for(int i = 0; i < m_tableDef.back(); ++i) {
        float &currentValueToCompare {qTable.at(firstElementPositionInMemory+i)};
        if(currentValueToCompare > max) max = currentValueToCompare;
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

