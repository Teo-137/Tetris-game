#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

using namespace std;

typedef vector<vector<int>> Shape;

class Block {
public:
    Shape shape;
    int x, y;

    Block(Shape s);
    void rotate();
};

#endif
