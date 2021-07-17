#ifndef GOBANG2_GOBANG_H
#define GOBANG2_GOBANG_H

#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <map>

#include <iostream>

using std::vector, std::pair, std::stack, std::map, std::sort, std::max, std::min;

class Gobang {
    vector<vector<int> > board{17, vector<int>(17, 0)};
    stack<pair<int, int> > record;
    int turn = 1;

    vector<vector<int *> > winningArray{572, vector<int *>(5)};
    vector<vector<int> > isValid{17, vector<int>(17, 0)};
    map<int, pair<pair<int, int>, pair<int, int> > > winningArrayDic;
    int winningPosition = 0;

public:
    Gobang();

    void initialize();

    int getTurn();

    [[maybe_unused]] vector<vector<int> > getBoard();

    stack<pair<int, int> > getRecord();

    pair<int, int> getPrevPiece();

    [[maybe_unused]] int check(pair<int, int>);

    int drop(pair<int, int>);

    void undo();

    int judge();

    pair<pair<int, int>, pair<int, int> > getWinningPos();

    pair<int, int> next();

private:
    int evaluateBoard();

    int evaluatePoint(pair<int, int>);

    vector<int> getLine(int, pair<int, int>);

    static int analysisLine(const vector<int> &, int);

    static int analysisPoint_my(const vector<int> &, int);

    static int analysisPoint_adversary(const vector<int> &, int);

    int alphaBeta(int, int, int, pair<int, int> * = nullptr);
};

#endif