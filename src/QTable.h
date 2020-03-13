//
// Created by Matthew Round on 11/03/2020.
//

#ifndef RSLR_QTABLE_H
#define RSLR_QTABLE_H


#include <vector>
class QTable {

public:
    explicit QTable(int x, int y, int z);
    std::vector<float> qTable;
    float& get(int x, int y, int z);
    void update(int x, int y, int z, float value);
    std::vector<float> get(int x, int y);
    void randomFill();
    float maxFutureQ(int x, int y);
private:
    const int m_width;
    const int m_height;
    const int m_depth;
    float randomFloat(float min, float max);
};


#endif //RSLR_QTABLE_H
