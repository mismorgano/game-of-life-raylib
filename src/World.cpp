//
// Created by Anton on 05/12/2023.
//

#include "World.h"
#include <utility>
#include <vector>
#include <ranges>
#include <set>

using namespace std;

#include "raylib.h"

bool World::isInWorld(const int row, int column) const {
    return 0 <= row && row < rows && 0 <= column && column < columns;
}


int World::count_neighbors(int row, int column) const {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        //rows
        for (int j = -1; j <= 1; ++j) {
            // columns
            if (i == 0 && j == 0) continue;
            const int current_row = row + i;
            const int current_col = column + j;
            if (isInWorld(current_row, current_col))
                count += cells[current_row][current_col];
        }
    }
    return count;
}

World::World(int rows, int columns, std::vector<std::pair<int, int> > aliveCells)
    : rows(rows), columns(columns), aliveCells(std::move(aliveCells)) {
    for (const auto &i: views::iota(1, rows)) {
        cells.emplace_back(columns);
    }
    for (const auto &cell: this->aliveCells) {
        int row = cell.first;
        int column = cell.second;
        cells[row][column] = 1;
    }
}

void World::makeAlive(int row, int column) {
}

void World::update() {
    vector<pair<int, int> > livingCells{};
    vector<pair<int, int> > deadCells{};
    set<pair<int, int> > cellsToCheck{};
    for (const auto &cell: aliveCells) {
        int row = cell.first;
        int column = cell.second;
        for (int i = -1; i <= 1; i++) {
            //rows
            for (int j = -1; j <= 1; ++j) {
                // columns
                const int current_row = row + i;
                const int current_col = column + j;
                if (isInWorld(current_row, current_col))
                    cellsToCheck.emplace(current_row, current_col);
            }
        }
    }
    for (const auto &cell: cellsToCheck) {
        int row = cell.first;
        int column = cell.second;
        int cn = count_neighbors(row, column);
        if (cn == 3)
            livingCells.emplace_back(row, column);
        else if (cells[row][column] == 1 && cn == 2) {
            livingCells.emplace_back(row, column);
        } else {
            deadCells.emplace_back(row, column);
        }
    }
    for (const auto &cell: livingCells) {
        int row = cell.first;
        int column = cell.second;
        cells[row][column] = 1;
    }
    for (const auto &cell: deadCells) {
        int row = cell.first;
        int column = cell.second;
        cells[row][column] = 0;
    }
    aliveCells = livingCells;
}

void World::draw(int cellSize) {
    for (const auto &cell: aliveCells) {
        int row = cell.first;
        int column = cell.second;
        DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, GRAY);
    }

    // for (size_t row = 0; row < rows; row++)
    // {
    //     for (size_t col = 0; col < columns; col++)
    //     {
    //         if(cells[row][col]) {
    //             DrawRectangle(col*cellSize, row*cellSize, cellSize, cellSize, RED);
    //         }
    //     }

    // }
}
