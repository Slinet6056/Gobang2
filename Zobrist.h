#ifndef GOBANG2_ZOBRIST_H
#define GOBANG2_ZOBRIST_H

#include <random>
#include <chrono>
#include <vector>
#include <ctime>
#include <utility>

class Zobrist {
    std::vector<std::vector<unsigned __int64> > board1, board2;

    static unsigned __int64 rand64();

public:
    unsigned __int64 key = rand64();

    Zobrist(int, int);

    void drop(std::pair<int, int>, int);

    void undo(std::pair<int, int>, int);
};

#endif