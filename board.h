#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Block.h"

using namespace std;

class Board {
private:
    vector<vector<int>> grid;

public:
    Board();
    bool canPlace(Block& block);
    void place(Block& block);
    int clearLines();
    void print(Block* currentBlock);
    void clearGrid();
};

#endif
