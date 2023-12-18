//
// Created by Anton on 05/12/2023.
//


#ifndef WORLD_H
#define WORLD_H

#include <vector>


class World {
    int rows;
    int columns;
    bool isInWorld(int row, int column)const;
    [[nodiscard]] int count_neighbors(int row, int column) const;
    std::vector<std::vector<unsigned short >> cells;
    std::vector<std::pair<int, int>> aliveCells;
    void makeAlive(int row, int column);

public:
    World(int rows, int columns, std::vector<std::pair<int, int>> aliveCells);
    void update();
    void draw(int cellSize);
};





#endif //WORLD_H
