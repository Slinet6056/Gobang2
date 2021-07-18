#include "Zobrist.h"

Zobrist::Zobrist(int m, int n) {
    board1.assign(m + 1, std::vector<unsigned __int64>(n + 1, rand64()));
    board2.assign(m + 1, std::vector<unsigned __int64>(n + 1, rand64()));
}

unsigned __int64 Zobrist::rand64() {
    std::independent_bits_engine<std::default_random_engine, 64, unsigned long long> rndEngine(std::chrono::system_clock::now().time_since_epoch().count());
    return rndEngine();
}

void Zobrist::drop(std::pair<int, int> pos, int turn) {
    if (turn == 1)
        key ^= board1[pos.first][pos.second];
    else
        key ^= board2[pos.first][pos.second];
}

void Zobrist::undo(std::pair<int, int> pos, int turn) {
    if (turn == 1)
        key ^= board1[pos.first][pos.second];
    else
        key ^= board2[pos.first][pos.second];
}