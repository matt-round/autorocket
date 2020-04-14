//
// Created by Matthew Round on 11/03/2020.
//

#ifndef RSLR_QTABLE_H
#define RSLR_QTABLE_H


#include <vector>
class QTable {

public:
    explicit QTable(std::vector<int> qTableDef);
    std::unique_ptr<std::vector<float>> qTable;
    float& get(std::vector<int> position);
    void update(std::vector<int> position, float value);
    std::vector<float> getRow(std::vector<int> position);
    void randomFill();
    float maxFutureQ(std::vector<int> position);
    void saveToFile(std::string path);
    void loadFromFile(std::string path);
    void printQTable();
private:
    const std::vector<int> m_tableDef;
    float randomFloat(float min, float max);
    int m_elementPosition(std::vector<int> position) ;
};


#endif //RSLR_QTABLE_H
