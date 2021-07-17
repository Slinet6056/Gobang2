#ifndef GOBANG2_PLAY_H
#define GOBANG2_PLAY_H

#include "Gobang.h"
#include "EasyX.h"

class Play {
    int firstPlayer = 1, secondPlayer = 1;
    Gobang gobang;
public:
    void initialize();

    void setMode();

    int run();
};

#endif