#include "Block.h"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

Block::Block(Shape s) : shape(s), x(BOARD_WIDTH / 2 - s[0].size() / 2), y(0) {}

//Obrócenie bloku o 90 stopni
void Block::rotate() {
    Shape rotated(shape[0].size(), vector<int>(shape.size()));
    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[0].size(); ++j) {
            rotated[j][shape.size() - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
}
