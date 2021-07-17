#ifndef GOBANG2_EASYX_H
#define GOBANG2_EASYX_H

#include <graphics.h>
#include <conio.h>
#include <utility>
#include <stack>

#define myBLACK RGB(75, 74, 73)
#define myWHITE RGB(255, 253, 249)
#define BKCOLOR RGB(247, 238, 214)

using std::pair, std::stack;

class EasyX {
public:
    static void initialize();

    static pair<int, int> setMode();

    static pair<int, int> getMousePos();

    static void printPieces(pair<int, int>, pair<int, int>, int);

    static void undo(int, int, stack<pair<int, int>>);

    static int showWinner(pair<int, int>, pair<int, int>);
};

#endif