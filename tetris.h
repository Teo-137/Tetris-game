#ifndef TETRIS_H
#define TETRIS_H

#include "Board.h"
#include <string>
#include <chrono>
#include <tuple>

class Tetris {
private:
    Board board;
    Block currentBlock;
    bool gameOver;
    bool endlessMode;
    int score;
    std::chrono::steady_clock::time_point lastUpdate;
    std::string playerName;
    double dropSpeed;

public:
    Tetris();
    void quit();
    void spawnBlock();
    void moveBlock(int dx, int dy);
    void rotateBlock();
    void setDifficulty();
    void showHighScores();
    void saveHighScore();
    void run();
    int scorePerLines(int linesCleared);
};

#endif
