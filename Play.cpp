#include "Play.h"

void Play::initialize() {
    EasyX::initialize();
    gobang.initialize();
    firstPlayer = 1;
    secondPlayer = 1;
}

void Play::setMode() {
    pair<int, int> mode = EasyX::setMode();
    firstPlayer = mode.first;
    secondPlayer = mode.second;
}

int Play::run() {
    int turn;
    pair<int, int> pos, prePos;
    while (true) {
        turn = gobang.getTurn();
        if (turn == 0) {  //平局
            return 0;
        } else if (turn == 1 && firstPlayer == 1 || turn == 2 && secondPlayer == 1) {
            do {
                pos = EasyX::getMousePos();
                turn = gobang.getTurn();
                if (pos.first == -1)  //重新开始
                    return -1;
                else if (pos.first == -2) {  //悔棋
                    auto record = gobang.getRecord();
                    if (turn == 1 && secondPlayer == 1 || turn == 2 && firstPlayer == 1) {  //玩家之间对战悔棋时撤销一步棋
                        if (!record.empty()) {
                            EasyX::undo(1, 1, record);
                            gobang.undo();
                        }
                    } else {  //玩家与电脑对战悔棋时撤销两部棋
                        if (record.size() > 1) {
                            EasyX::undo(2, 1, record);
                            gobang.undo();
                            gobang.undo();
                        }
                    }
                } else if (pos.first == -3) {  //提示
                    pos = gobang.next();
                }
            } while (gobang.drop(pos));
            prePos = gobang.getPrevPiece();
            EasyX::printPieces(pos, prePos, turn);
        } else {
            pos = gobang.next();
            gobang.drop(pos);
            prePos = gobang.getPrevPiece();
            EasyX::printPieces(pos, prePos, turn);
        }
        int res = gobang.judge();
        if (res) {
            pair<pair<int, int>, pair<int, int> > winningPos = gobang.getWinningPos();
            res = EasyX::showWinner(winningPos.first, winningPos.second);
            if (res == -1)  //重新开始
                return -1;
            else if (res == -2) {  //悔棋
                auto record = gobang.getRecord();
                turn = gobang.getTurn();
                if (turn == 1 && secondPlayer == 1 || turn == 2 && firstPlayer == 1) {  //玩家之间对战悔棋时撤销一步棋
                    EasyX::undo(1, 2, record);
                    gobang.undo();
                } else {  //玩家与电脑对战悔棋时撤销两部棋
                    EasyX::undo(2, 2, record);
                    gobang.undo();
                    gobang.undo();
                }
            }
        }
    }
}