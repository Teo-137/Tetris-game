#include "Board.h"
#include <algorithm>
#include <iostream>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

Board::Board() : grid(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0)) {}

//Sprawdzenie czy blok może zostać umieszczony w danym miejscu na planszy
bool Board::canPlace(Block& block) {
    for (size_t i = 0; i < block.shape.size(); ++i) {
        for (size_t j = 0; j < block.shape[0].size(); ++j) {
            if (block.shape[i][j]) {
                int nx = block.x + j;
                int ny = block.y + i;
                if (nx < 0 || nx >= BOARD_WIDTH || ny < 0 || ny >= BOARD_HEIGHT || grid[ny][nx]) {
                    return false;
                }
            }
        }
    }
    return true;
}
//Umieszczenie bloku na planszy
void Board::place(Block& block) {
    for (size_t i = 0; i < block.shape.size(); ++i) {
        for (size_t j = 0; j < block.shape[0].size(); ++j) {
            if (block.shape[i][j]) {
                grid[block.y + i][block.x + j] = 1;
            }
        }
    }
}
//Usunięcie zapełnionych linii i wstawienie nowych pustych
int Board::clearLines() {
    int cleared = 0;
    for (int i = BOARD_HEIGHT - 1; i >= 0; --i) {
        if (all_of(grid[i].begin(), grid[i].end(), [](int cell) { return cell == 1; })) {
            grid.erase(grid.begin() + i);
            grid.insert(grid.begin(), vector<int>(BOARD_WIDTH, 0));
            cleared++;
            ++i;
        }
    }
    return cleared;
}
//Wypisanie na wyjściu aktualnej planszy
void Board::print(Block* currentBlock) {
    vector<vector<int>> tempGrid = grid;

    if (currentBlock) {
        for (size_t i = 0; i < currentBlock->shape.size(); ++i) {
            for (size_t j = 0; j < currentBlock->shape[0].size(); ++j) {
                if (currentBlock->shape[i][j]) {
                    int x = currentBlock->x + j;
                    int y = currentBlock->y + i;
                    if (y >= 0 && y < BOARD_HEIGHT && x >= 0 && x < BOARD_WIDTH) {
                        tempGrid[y][x] = 1;
                    }
                }
            }
        }
    }

    for (const auto& row : tempGrid) {
        for (const auto& cell : row) {
            cout << (cell ? '#' : '-');
        }
        cout << '\n';
    }
    cout << string(20, '~') << '\n';
}

//Wyczyszczenie planszy po zakończeniu gr
void Board::clearGrid() {
    for (auto& row : grid) {
        fill(row.begin(), row.end(), 0);
    }
}
