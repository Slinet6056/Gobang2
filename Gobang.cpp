#include "Gobang.h"

Gobang::Gobang() {
    int cnt = 0;
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 11; ++j) {
            for (int k = 0; k < 5; ++k) {
                winningArray[cnt][k] = &board[i][j + k];
                winningArray[cnt + 1][k] = &board[j + k][i];
            }
            winningArrayDic[cnt] = {{i, j},
                                    {i, j + 4}};
            winningArrayDic[cnt + 1] = {{j,     i},
                                        {j + 4, i}};
            cnt += 2;
        }
    }
    for (int j = 1; j <= 11; ++j) {
        for (int k = 0; k < 5; ++k) {
            winningArray[cnt][k] = &board[j + k][j + k];
            winningArray[cnt + 1][k] = &board[j + k][16 - j - k];
        }
        winningArrayDic[cnt] = {{j,     j},
                                {j + 4, j + 4}};
        winningArrayDic[cnt + 1] = {{j,     16 - j},
                                    {j + 4, 12 - j}};
        cnt += 2;
    }
    for (int i = 2; i <= 11; ++i) {
        for (int j = 1; j <= 12 - i; ++j) {
            for (int k = 0; k < 5; ++k) {
                winningArray[cnt][k] = &board[i + j + k - 1][j + k];
                winningArray[cnt + 1][k] = &board[j + k][i + j + k - 1];
                winningArray[cnt + 2][k] = &board[17 - i - j - k][j + k];
                winningArray[cnt + 3][k] = &board[16 - j - k][i + j + k - 1];
            }
            winningArrayDic[cnt] = {{i + j - 1, j},
                                    {i + j + 3, j + 4}};
            winningArrayDic[cnt + 1] = {{j,     i + j - 1},
                                        {j + 4, i + j + 3}};
            winningArrayDic[cnt + 2] = {{17 - i - j, j},
                                        {13 - i - j, j + 4}};
            winningArrayDic[cnt + 3] = {{16 - j, i + j - 1},
                                        {12 - j, i + j + 3}};
            cnt += 4;
        }
    }
    isValid[8][8] = 1;
}

void Gobang::initialize() {
    turn = 1;
    board.assign(17, vector<int>(17, 0));
    isValid.assign(17, vector<int>(17, 0));
    isValid[8][8] = 1;
    while (!record.empty())
        record.pop();
}

int Gobang::getTurn() {
    if (record.size() == 255)
        return 0;
    else
        return turn;
}

[[maybe_unused]] vector<vector<int>> Gobang::getBoard() {
    return board;
}

stack<pair<int, int> > Gobang::getRecord() {
    return record;
}

pair<int, int> Gobang::getPrevPiece() {
    if (record.size() <= 1)
        return {-1, -1};
    else {
        auto temp = record;
        temp.pop();
        return temp.top();
    }
}

[[maybe_unused]] int Gobang::check(pair<int, int> p) {
    if (p.first < 1 || p.first > 15 || p.second < 1 || p.second > 15)
        return -1;
    return board[p.first][p.second];
}

int Gobang::drop(pair<int, int> p) {
    if (p.first < 1 || p.first > 15 || p.second < 1 || p.second > 15 || board[p.first][p.second])
        return 1;
    board[p.first][p.second] = turn;
    for (int i = max(1, p.first - 2); i <= min(15, p.first + 2); ++i)
        for (int j = max(1, p.second - 2); j <= min(15, p.second + 2); ++j)
            ++isValid[i][j];
    record.push(p);
    turn = 3 - turn;
    return 0;
}

void Gobang::undo() {
    if (record.empty())
        return;
    pair<int, int> p = record.top();
    board[p.first][p.second] = 0;
    for (int i = max(1, p.first - 2); i <= min(15, p.first + 2); ++i)
        for (int j = max(1, p.second - 2); j <= min(15, p.second + 2); ++j)
            --isValid[i][j];
    record.pop();
    turn = 3 - turn;
}

int Gobang::judge() {
    for (int i = 0; i < 572; ++i) {
        int temp = 1;
        for (int j = 0; j < 5; ++j)
            temp *= *winningArray[i][j];
        if (temp == 1) {
            winningPosition = i;
            return 1;
        } else if (temp == 32) {
            winningPosition = i;
            return 2;
        }
    }
    return 0;
}

pair<pair<int, int>, pair<int, int> > Gobang::getWinningPos() {
    return winningArrayDic[winningPosition];
}

pair<int, int> Gobang::next() {
    pair<int, int> pos;
    if (record.size() < 3 || record.size() > 150)
        alphaBeta(6, INT_MIN, INT_MAX, &pos);
    else if (record.size() > 170)
        alphaBeta(4, INT_MIN, INT_MAX, &pos);
    else
        alphaBeta(8, INT_MIN, INT_MAX, &pos);
    return pos;
}

int Gobang::alphaBeta(int depth, int alpha, int beta, pair<int, int> *pos) {
    if (judge() || !depth || !getTurn())
        return evaluateBoard();
    int score;
    vector<pair<int, pair<int, int> > > candidates;
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 15; ++j) {
            if (!board[i][j] && isValid[i][j]) {
                drop({i, j});
                candidates.push_back({evaluatePoint({i, j}) - (int) sqrt((i - 8) * (i - 8) + (j - 8) * (j - 8)), {i, j}});
                undo();
            }
        }
    }
    sort(candidates.begin(), candidates.end(), [](const auto &a, const auto &b) {
        return a.first > b.first;
    });
    if (turn == 1) {
        score = INT_MIN;
        for (int i = 0; i < candidates.size() && i < 7; ++i) {
            auto x = candidates[i].second;
            drop(x);
            int res = alphaBeta(depth - 1, alpha, beta) - (int) sqrt((x.first - 8) * (x.first - 8) + (x.second - 8) * (x.second - 8));
            if (res > score) {
                score = res;
                if (pos)
                    *pos = x;
            }
            undo();
            alpha = max(alpha, score);
            if (alpha >= beta)
                break;
        }
    } else {
        score = INT_MAX;
        for (int i = 0; i < candidates.size() && i < 7; ++i) {
            auto x = candidates[i].second;
            drop(x);
            int res = alphaBeta(depth - 1, alpha, beta) + (int) sqrt((x.first - 8) * (x.first - 8) + (x.second - 8) * (x.second - 8));
            if (res < score) {
                score = res;
                if (pos)
                    *pos = x;
            }
            undo();
            beta = min(beta, score);
            if (alpha >= beta)
                break;
        }
    }
    return score;
}

int Gobang::evaluateBoard() {
    int score = 0;
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 15; ++j) {
            if (board[i][j]) {
                for (int direction = 1; direction <= 4; ++direction) {  // 1:- 2:| 3:\ 4:/
                    score += analysisLine(getLine(direction, {i, j}), board[i][j]) * (board[i][j] == 1 ? 1 : -1);
                }
            }
        }
    }
    return score;
}

int Gobang::evaluatePoint(pair<int, int> pos) {
    int myScore = 0, opponentScore = 0;
    for (int direction = 1; direction <= 4; direction++) { // 1:- 2:| 3:\ 4:/
        const auto &line = getLine(direction, pos);
        myScore += analysisPoint_my(line, turn);
        opponentScore += analysisPoint_adversary(line, turn);
    }
    return myScore + opponentScore;
}

vector<int> Gobang::getLine(int direction, pair<int, int> pos) {
    vector<int> line(12, -1);
    switch (direction) {
        case 1:
            for (int i = -5; i <= 5; ++i)
                if (pos.second + i >= 1 && pos.second + i <= 15)
                    line[i + 5] = board[pos.first][pos.second + i];
                else
                    line[i + 5] = -1;
            break;
        case 2:
            for (int i = -5; i <= 5; ++i)
                if (pos.first + i >= 1 && pos.first + i <= 15)
                    line[i + 5] = board[pos.first + i][pos.second];
                else
                    line[i + 5] = -1;
            break;
        case 3:
            for (int i = -5; i <= 5; ++i)
                if (pos.first + i >= 1 && pos.second + i >= 1 && pos.first + i <= 15 && pos.second + i <= 15)
                    line[i + 5] = board[pos.first + i][pos.second + i];
                else
                    line[i + 5] = -1;
            break;
        case 4:
            for (int i = -5; i <= 5; ++i)
                if (pos.first + i >= 1 && pos.second - i >= 1 && pos.first + i <= 15 && pos.second - i <= 15)
                    line[i + 5] = board[pos.first + i][pos.second - i];
                else
                    line[i + 5] = -1;
            break;
        default:
            break;
    }
    return line;
}

int Gobang::analysisLine(const vector<int> &line, int t) {
    int score = 0, leftRange = 5, rightRange = 5;
    for (; leftRange > 0 && line[leftRange - 1] == t; --leftRange);
    for (; rightRange < 11 && line[rightRange + 1] == t; ++rightRange);
    switch (rightRange - leftRange + 1) {
        default:
            return 2000000;
        case 4:
            if (line[leftRange - 1] == 0 && line[rightRange + 1] == 0)
                return 250; //011110
            else if ((line[leftRange - 1] == 0) || (line[rightRange + 1] == 0))
                return 75; //011112|211110
            break;
        case 3:
            if (line[leftRange - 1] == 0 && line[rightRange + 1] == 0) {
                if ((line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) &&
                    (line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1))
                    return 15; //2011102
                else if ((line[leftRange - 2] == 0 && line[rightRange + 2] == 0) ||
                         ((line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) && line[rightRange + 2] == 0) ||
                         ((line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1) && line[leftRange - 2] == 0))
                    return 65; //0011100|2011100|0011102
            }
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && (line[rightRange + 1] == 3 - t || line[rightRange + 1] == -1))
                return 15; //001112
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && (line[leftRange - 1] == 3 - t || line[leftRange - 1] == -1))
                return 15; //211100
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t)
                score += 75; //10111
            if (line[rightRange + 2] == t && line[rightRange + 1] == 0)
                score += 75; //11101
            break;
        case 2:
            if ((line[leftRange - 1] == 3 - t || line[leftRange - 1] == -1) && line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == 0)
                return 15; //211010
            if ((line[rightRange + 1] == 3 - t || line[rightRange + 1] == -1) && line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == 0)
                return 15; //010112
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[rightRange + 1] == 0 && line[rightRange + 2] == 0)
                return 15; //001100
            else if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0) {
                if (line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1) {
                    if (line[leftRange - 3] == 0)
                        return 15; //0001102
                    else if (line[leftRange - 3] == 3 - t || line[leftRange - 3] == -1)
                        return 2; //2001102
                }
            } else if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0) {
                if (line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) {
                    if (line[rightRange + 3] == 0)
                        return 15; //2011000
                    else if (line[rightRange + 3] == 3 - t || line[rightRange + 3] == -1)
                        return 2; //2011002
                }
            }
            if ((line[leftRange - 1] != 0 && line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && line[rightRange + 3] == 0) ||
                (line[rightRange + 1] != 0 && line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[leftRange - 3] == 0))
                return 2; //211000|000112
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == t)
                score += 75; //11011
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == t)
                score += 75; //11011
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && (line[leftRange - 3] == 3 - t || line[leftRange - 3] == -1) && line[rightRange + 1] == 0)
                score += 15; //210110
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && (line[rightRange + 3] == 3 - t || line[rightRange + 3] == -1) && line[leftRange - 1] == 0)
                score += 15; //011012
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == 0 && line[rightRange + 1] == 0)
                score += 65; //010110
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == 0 && line[leftRange - 1] == 0)
                score += 65; //011010
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[leftRange - 3] == t)
                score += 15; //10011
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && line[rightRange + 3] == t)
                score += 15; //11001
            break;
        case 1:
            if (line[4] == 0 && line[3] == t && line[2] == t && line[1] == t)
                score += 75; //11101
            if (line[6] == 0 && line[7] == t && line[8] == t && line[9] == t)
                score += 75; //10111
            if (line[4] == 0 && line[3] == t && line[2] == t) {
                if ((line[1] == 3 - t || line[1] == -1) && line[6] == 0)
                    score += 15; //211010
                else if (line[1] == 0 && (line[6] == 3 - t || line[6] == -1))
                    return 15; //011012
                else if (line[1] == 0 && line[6] == 0)
                    score += 65; //011010
            }
            if (line[6] == 0 && line[7] == t && line[8] == t) {
                if (line[4] == 0 && (line[9] == 3 - t || line[9] == -1))
                    score += 15; //010112
                else if ((line[4] == 4 - t || line[4] == -1) && line[9] == 0)
                    return 15; //210110
                else if (line[4] == 0 && line[9] == 0)
                    score += 65; //010110
            }
            if ((line[4] == 0 && line[3] == 0 && line[2] == 0 && line[1] == t) || (line[6] == 0 && line[7] == 0 && line[8] == 0 && line[9] == t))
                score += 2; //10001
            if (line[4] == 0 && line[3] == 0 && line[2] == t) {
                if (line[1] == 0 && line[6] == 0)
                    score += 15; //010010
                else if (line[1] == 0 && (line[6] == 3 - t || line[6] == -1))
                    return 2; //010012
                else if ((line[1] == 3 - t || line[1] == -1) && line[6] == 0)
                    score += 2; //210010
                else if (line[1] == t)
                    score += 15; //11001
            }
            if (line[6] == 0 && line[7] == 0 && line[8] == t) {
                if (line[4] == 0 && line[9] == 0)
                    score += 15; //010010
                else if ((line[4] == 3 - t || line[4] == -1) && line[9] == 0)
                    return 2; //210010
                else if (line[4] == 0 && (line[9] == 3 - t || line[9] == -1))
                    score += 2; //010012
                else if (line[9] == t)
                    score += 15; //10011
            }
            if (line[4] == 0 && line[3] == t && line[6] == 0 && line[7] == t)
                return 15; //10101
            if (line[4] == 0 && line[3] == t && line[2] == 0 && line[1] == t)
                score += 15; //10101
            if (line[6] == 0 && line[7] == t && line[8] == 0 && line[9] == t)
                score += 15; //10101
            if (line[4] == 0 && line[3] == t) {
                if (line[2] == 0 && line[6] == 0) {
                    if ((line[1] == 3 - t || line[1] == -1) && (line[7] == 3 - t || line[7] == -1))
                        return 2; //2010102
                    else if (line[7] == 3 - t || line[7] == -1)
                        return 15; //0010102
                    else
                        score += 15; //2010100|0010100
                } else if ((line[2] == 3 - t || line[2] == -1) && line[6] == 0 && line[7] == 0)
                    score += 2; //210100
                else if (line[2] == 0 && line[1] == 0 && line[6] != 0)
                    return 2; //001012
            }
            if (line[6] == 0 && line[7] == t) {
                if (line[8] == 0 && line[4] == 0) {
                    if ((line[3] == 3 - t || line[3] == -1) && (line[9] == 3 - t || line[9] == -1))
                        return 2; //2010102
                    else if (line[3] == 3 - t || line[3] == -1)
                        return 15; //2010100
                    else
                        score += 15; //0010102|0010100
                } else if ((line[8] == 3 - t || line[8] == -1) && line[4] == 0 && line[3] == 0) {
                    score += 2; //001012
                } else if (line[8] == 0 && line[9] == 0 && (line[4] == 3 - t || line[4] == -1))
                    return 2; //210100
            }
            break;
    }
    return score;
}

int Gobang::analysisPoint_my(const vector<int> &line, int t) {
    int myScore = 0, leftRange = 5, rightRange = 5;
    for (; line[leftRange - 1] == t; leftRange--);
    for (; line[rightRange + 1] == t; rightRange++);
    switch (rightRange - leftRange + 1) {
        case 5:
            return 10000000;
        case 4:
            if (line[leftRange - 1] == 0 && line[rightRange + 1] == 0)
                return 1000; //011110
            else if ((line[leftRange - 1] == 0) || (line[rightRange + 1] == 0))
                return 300; //011112|211110
            break;
        case 3:
            if (line[leftRange - 1] == 0 && line[rightRange + 1] == 0) {
                if ((line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) &&
                    (line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1))
                    return 50; //2011102
                else if ((line[leftRange - 2] == 0 && line[rightRange + 2] == 0) ||
                         ((line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) && line[rightRange + 2] == 0) ||
                         ((line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1) && line[leftRange - 2] == 0))
                    return 200; //0011100|2011100|0011102
            }
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && (line[rightRange + 1] == 3 - t || line[rightRange + 1] == -1))
                return 50; //001112
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && (line[leftRange - 1] == 3 - t || line[leftRange - 1] == -1))
                return 50; //211100
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t)
                myScore += 300; //10111
            if (line[rightRange + 2] == t && line[rightRange + 1] == 0)
                myScore += 300; //11101
            break;
        case 2:
            if ((line[leftRange - 1] == 3 - t || line[leftRange - 1] == -1) && line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == 0)
                return 50; //211010
            if ((line[rightRange + 1] == 3 - t || line[rightRange + 1] == -1) && line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == 0)
                return 50; //010112
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[rightRange + 1] == 0 && line[rightRange + 2] == 0)
                return 30; //001100
            else if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0) {
                if (line[rightRange + 2] == 3 - t || line[rightRange + 2] == -1) {
                    if (line[leftRange - 3] == 0)
                        return 30; //0001102
                    else if (line[leftRange - 3] == 3 - t || line[leftRange - 3] == -1)
                        return 5; //2001102
                }
            } else if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0) {
                if (line[leftRange - 2] == 3 - t || line[leftRange - 2] == -1) {
                    if (line[rightRange + 3] == 0)
                        return 30; //2011000
                    else if (line[rightRange + 3] == 3 - t || line[rightRange + 3] == -1)
                        return 5; //2011002
                }
            }
            if ((line[leftRange - 1] != 0 && line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && line[rightRange + 3] == 0) ||
                (line[rightRange + 1] != 0 && line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[leftRange - 3] == 0))
                return 5; //211000|000112
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == t)
                myScore += 300; //11011
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == t)
                myScore += 300; //11011
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && (line[leftRange - 3] == 3 - t || line[leftRange - 3] == -1) && line[rightRange + 1] == 0)
                myScore += 50; //210110
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && (line[rightRange + 3] == 3 - t || line[rightRange + 3] == -1) && line[leftRange - 1] == 0)
                myScore += 50; //011012
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == t && line[leftRange - 3] == 0 && line[rightRange + 1] == 0)
                myScore += 200; //010110
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == t && line[rightRange + 3] == 0 && line[leftRange - 1] == 0)
                myScore += 200; //011010
            if (line[leftRange - 1] == 0 && line[leftRange - 2] == 0 && line[leftRange - 3] == t)
                myScore += 50; //10011
            if (line[rightRange + 1] == 0 && line[rightRange + 2] == 0 && line[rightRange + 3] == t)
                myScore += 50; //11001
            break;
        case 1:
            if (line[4] == 0 && line[3] == t && line[2] == t && line[1] == t)
                myScore += 300; //11101
            if (line[6] == 0 && line[7] == t && line[8] == t && line[9] == t)
                myScore += 300; //10111
            if (line[4] == 0 && line[3] == t && line[2] == t) {
                if ((line[1] == 3 - t || line[1] == -1) && line[6] == 0)
                    myScore += 50; //211010
                else if (line[1] == 0 && (line[6] == 3 - t || line[6] == -1))
                    return 50; //011012
                else if (line[1] == 0 && line[6] == 0)
                    myScore += 200; //011010
            }
            if (line[6] == 0 && line[7] == t && line[8] == t) {
                if (line[4] == 0 && (line[9] == 3 - t || line[9] == -1))
                    myScore += 50; //010112
                else if ((line[4] == 4 - t || line[4] == -1) && line[9] == 0)
                    return 50; //210110
                else if (line[4] == 0 && line[9] == 0)
                    myScore += 200; //010110
            }
            if ((line[4] == 0 && line[3] == 0 && line[2] == 0 && line[1] == t) || (line[6] == 0 && line[7] == 0 && line[8] == 0 && line[9] == t))
                myScore += 5; //10001
            if (line[4] == 0 && line[3] == 0 && line[2] == t) {
                if (line[1] == 0 && line[6] == 0)
                    myScore += 30; //010010
                else if (line[1] == 0 && (line[6] == 3 - t || line[6] == -1))
                    return 5; //010012
                else if ((line[1] == 3 - t || line[1] == -1) && line[6] == 0)
                    myScore += 5; //210010
                else if (line[1] == t)
                    myScore += 50; //11001
            }
            if (line[6] == 0 && line[7] == 0 && line[8] == t) {
                if (line[4] == 0 && line[9] == 0)
                    myScore += 30; //010010
                else if ((line[4] == 3 - t || line[4] == -1) && line[9] == 0)
                    return 5; //210010
                else if (line[4] == 0 && (line[9] == 3 - t || line[9] == -1))
                    myScore += 5; //010012
                else if (line[9] == t)
                    myScore += 50; //10011
            }
            if (line[4] == 0 && line[3] == t && line[6] == 0 && line[7] == t)
                return 50; //10101
            if (line[4] == 0 && line[3] == t && line[2] == 0 && line[1] == t)
                myScore += 50; //10101
            if (line[6] == 0 && line[7] == t && line[8] == 0 && line[9] == t)
                myScore += 50; //10101
            if (line[4] == 0 && line[3] == t) {
                if (line[2] == 0 && line[6] == 0) {
                    if ((line[1] == 3 - t || line[1] == -1) && (line[7] == 3 - t || line[7] == -1))
                        return 5; //2010102
                    else if (line[7] == 3 - t || line[7] == -1)
                        return 30; //0010102
                    else
                        myScore += 30; //2010100|0010100
                } else if ((line[2] == 3 - t || line[2] == -1) && line[6] == 0 && line[7] == 0)
                    myScore += 5; //210100
                else if (line[2] == 0 && line[1] == 0 && line[6] != 0)
                    return 5; //001012
            }
            if (line[6] == 0 && line[7] == t) {
                if (line[8] == 0 && line[4] == 0) {
                    if ((line[3] == 3 - t || line[3] == -1) && (line[9] == 3 - t || line[9] == -1))
                        return 5; //2010102
                    else if (line[3] == 3 - t || line[3] == -1)
                        return 30; //2010100
                    else
                        myScore += 30; //0010102|0010100
                } else if ((line[8] == 3 - t || line[8] == -1) && line[4] == 0 && line[3] == 0) {
                    myScore += 5; //001012
                } else if (line[8] == 0 && line[9] == 0 && (line[4] == 3 - t || line[4] == -1))
                    return 5; //210100
            }
            break;
    }
    return myScore;
}

int Gobang::analysisPoint_adversary(const vector<int> &line, int t) {
    int opponentScore = 0, cntLeft = 0, cntRight = 0;
    for (; line[4 - cntLeft] == 3 - t; cntLeft++);
    for (; line[6 + cntRight] == 3 - t; cntRight++);
    switch (cntLeft) { // NOLINT(hicpp-multiway-paths-covered)
        case 4:
            if (line[0] == 0)
                opponentScore += 10000000 - 300; //011112
            else
                opponentScore += 10000000; //211112
            break;
        case 3:
            if (line[1] == 0) {
                if (line[0] == 0) {
                    if (line[6] == 0)
                        opponentScore += 1000 - 50; //0011120
                    else if (line[6] == t || line[6] == -1)
                        opponentScore += 300 - 50; //0011122
                } else if (line[0] == t || line[0] == -1) {
                    if (line[6] == 0)
                        opponentScore += 1000; //2011120
                    else if (line[6] == t || line[6] == -1)
                        opponentScore += 300; //2011122
                }
            } else if (line[1] == t || line[1] == -1) {
                if (line[6] == 0)
                    opponentScore += 300; //211120
            }
            break;
        case 2:
            if (line[2] == 0) {
                if (line[1] == 0) {
                    if (line[6] == 0) {
                        if (line[0] == 0)
                            opponentScore += 200 - 5; //0001120
                        else if (line[0] == t || line[0] == -1)
                            opponentScore += 200; //2001120
                    } else if (line[6] == t || line[6] == -1) {
                        if (line[0] == 0)
                            opponentScore += 200 - 5; //0001122
                        else if (line[0] == t || line[0] == -1)
                            opponentScore += 50; //2001122
                    }
                } else if (line[1] == 3 - t) {
                    if (line[0] == t || line[0] == -1)
                        opponentScore += 300; //210112
                } else if (line[1] == t || line[1] == -1) {
                    if (line[6] == 0) {
                        if (line[7] == 0)
                            opponentScore += 200; //2011200
                        else if (line[7] == t || line[7] == -1)
                            opponentScore += 50; //2011202
                    }
                }
            } else if (line[2] == t || line[2] == -1) {
                if (line[6] == 0 && line[7] == 0)
                    opponentScore += 50; //211200
            }
            break;
        case 1:
            if (line[3] == 0) {
                if (line[2] == 0) {
                    if (line[1] == 3 - t) {
                        if (line[0] == 0)
                            opponentScore += 50 - 5; //010012
                        else
                            opponentScore += 50; //210012
                    } else if (line[1] == t || line[1] == -1) {
                        if (line[6] == 0) {
                            if (line[7] == 0)
                                opponentScore += 30; //2001200
                            else if (line[7] == t || line[7] == -1)
                                opponentScore += 5; //2001202
                        }
                    } else if (line[1] == 0) {
                        if (line[6] == 0)
                            opponentScore += 30; //000120
                        else if (line[6] == t || line[6] == -1)
                            opponentScore += 5; //000122
                    }
                } else if (line[2] == 3 - t) {
                    if (line[1] == 0) {
                        if (line[6] == 0) {
                            if (line[0] == 0)
                                opponentScore += 200 - 5; //0010120
                            else
                                opponentScore += 200; //2010120
                        } else if (line[6] == t || line[6] == -1) {
                            if (line[0] == 0)
                                opponentScore += 50 - 5; //0010122
                            else
                                opponentScore += 50; //2010122
                        }
                    } else if (line[1] == 3 - t) {
                        if (line[0] == t || line[0] == -1)
                            opponentScore += 300; //211012
                    } else if (line[1] == t || line[1] == -1) {
                        if (line[6] == 0)
                            opponentScore += 50; //210120
                    }
                } else if (line[2] == t || line[2] == -1) {
                    if (line[6] == 0 && line[7] == 0 && line[8] == 0)
                        opponentScore += 30; //2012000
                    else if (line[6] == 0 && line[7] == 0 && (line[8] == t || line[8] == -1))
                        opponentScore += 5; //2012002
                }
            } else if (line[3] == t || line[3] == -1) {
                if (line[6] == 0 && line[7] == 0 && line[8] == 0)
                    opponentScore += 5; //212000
            }
            break;
        case 0:
            if (line[4] == 0) {
                if (line[3] == 0) {
                    if (line[2] == 0) {
                        if (line[1] == 3 - t)
                            opponentScore += 5; //10002
                    } else if (line[2] == 3 - t) {
                        if (line[1] == 0) {
                            if (line[6] == 0)
                                opponentScore += 30; //010020
                            else if (line[6] == t || line[6] == -1)
                                opponentScore += 5; //010022
                        } else if (line[1] == 3 - t) {
                            if (line[0] == 0)
                                opponentScore += 50 - 5; //011002
                            else
                                opponentScore += 50; //211002
                        } else if ((line[1] == t || line[1] == -1) && line[6] == 0)
                            opponentScore += 5; //210020
                    }
                } else if (line[3] == 3 - t) {
                    if (line[2] == 0) {
                        if (line[1] == 0) {
                            if (line[6] == 0)
                                opponentScore += 30; //001020
                            else if (line[6] == t || line[6] == -1)
                                opponentScore += 5; //001022
                        } else if (line[1] == 3 - t) {
                            if (line[0] == t || line[0] == -1)
                                opponentScore += 50; //210102
                            else if (line[0] == 0)
                                opponentScore += 50 - 5; //010102
                        } else if (line[1] == t || line[1] == -1) {
                            if (line[6] == 0) {
                                if (line[7] == 0)
                                    opponentScore += 30; //2010200
                                else if (line[7] == t || line[7] == -1)
                                    opponentScore += 5; //2010202
                            }
                        }
                    } else if (line[2] == 3 - t) {
                        if (line[1] == 0) {
                            if (line[0] == 0) {
                                if (line[6] == 0)
                                    opponentScore += 200 - 5; //0011020
                                else if (line[6] == t || line[6] == -1) {
                                    opponentScore += 50 - 5; //0011022
                                }
                            } else if (line[0] == t || line[0] == -1) {
                                if (line[6] == 0)
                                    opponentScore += 200; //2011020
                                else if (line[6] == t || line[6] == -1)
                                    opponentScore += 50; //2011022
                            }
                        } else if (line[1] == 3 - t) {
                            if (line[0] == t || line[0] == -1)
                                opponentScore += 300; //211102
                        } else if (line[1] == t || line[1] == -1) {
                            if (line[6] == 0)
                                opponentScore += 50; //211020
                        }
                    } else if (line[2] == t || line[2] == -1) {
                        if (line[6] == 0 && line[7] == 0)
                            opponentScore += 5; //210200
                    }
                }
            }
            break;
    }
    switch (cntRight) { // NOLINT(hicpp-multiway-paths-covered)
        case 4:
            if (line[10] == 0)
                opponentScore += 10000000 - 300; //211110
            else
                opponentScore += 10000000; //211112
            break;
        case 3:
            if (line[9] == 0) {
                if (line[10] == 0) {
                    if (line[4] == 0)
                        opponentScore += 1000 - 50; //0211100
                    else if (line[4] == t || line[4] == -1)
                        opponentScore += 300 - 50; //2211100
                } else if (line[10] == t || line[10] == -1) {
                    if (line[4] == 0)
                        opponentScore += 1000; //0211102
                    else if (line[4] == t || line[4] == -1)
                        opponentScore += 300; //2211102
                }
            } else if (line[9] == t || line[9] == -1) {
                if (line[4] == 0)
                    opponentScore += 300; //211120
            }
            break;
        case 2:
            if (line[8] == 0) {
                if (line[9] == 0) {
                    if (line[4] == 0) {
                        if (line[10] == 0)
                            opponentScore += 200 - 5; //0211000
                        else if (line[10] == t || line[10] == -1)
                            opponentScore += 200; //0211002
                    } else if (line[4] == t || line[4] == -1) {
                        if (line[10] == 0)
                            opponentScore += 200 - 5; //2211000
                        else if (line[10] == t || line[10] == -1)
                            opponentScore += 50; //2211002
                    }
                } else if (line[9] == 3 - t) {
                    if (line[10] == t || line[10] == -1)
                        opponentScore += 300; //211012
                } else if (line[9] == t || line[9] == -1) {
                    if (line[4] == 0) {
                        if (line[3] == 0)
                            opponentScore += 200; //0021102
                        else if (line[3] == t || line[3] == -1)
                            opponentScore += 50; //2021102
                    }
                }
            } else if (line[8] == t || line[8] == -1) {
                if (line[4] == 0 && line[3] == 0)
                    opponentScore += 50; //002112
            }
            break;
        case 1:
            if (line[7] == 0) {
                if (line[8] == 0) {
                    if (line[9] == 3 - t) {
                        if (line[10] == 0)
                            opponentScore += 50 - 5; //210010
                        else
                            opponentScore += 50; //210012
                    } else if (line[9] == t || line[9] == -1) {
                        if (line[4] == 0) {
                            if (line[3] == 0)
                                opponentScore += 30; //0021002
                            else if (line[3] == t || line[3] == -1)
                                opponentScore += 5; //2021002
                        }
                    } else if (line[9] == 0) {
                        if (line[4] == 0)
                            opponentScore += 30; //021000
                        else if (line[4] == t || line[4] == -1)
                            opponentScore += 5; //221000
                    }
                } else if (line[8] == 3 - t) {
                    if (line[9] == 0) {
                        if (line[4] == 0) {
                            if (line[10] == 0)
                                opponentScore += 200 - 5; //0210100
                            else
                                opponentScore += 200; //0210102
                        } else if (line[4] == t || line[4] == -1) {
                            if (line[10] == 0)
                                opponentScore += 50 - 5; //2210100
                            else
                                opponentScore += 50; //2210102
                        }
                    } else if (line[9] == 3 - t) {
                        if (line[10] == t || line[10] == -1)
                            opponentScore += 300; //210112
                    } else if (line[9] == t || line[9] == -1) {
                        if (line[4] == 0)
                            opponentScore += 50; //021012
                    }
                } else if (line[8] == t || line[8] == -1) {
                    if (line[4] == 0 && line[3] == 0 && line[2] == 0)
                        opponentScore += 30; //0002102
                    else if (line[4] == 0 && line[3] == 0 && (line[2] == t || line[2] == -1))
                        opponentScore += 5; //2002102
                }
            } else if (line[7] == t || line[7] == -1) {
                if (line[4] == 0 && line[3] == 0 && line[2] == 0)
                    opponentScore += 5; //000212
            }
            break;
        case 0:
            if (line[6] == 0) {
                if (line[7] == 0) {
                    if (line[8] == 0) {
                        if (line[9] == 3 - t)
                            opponentScore += 5; //20001
                    } else if (line[8] == 3 - t) {
                        if (line[9] == 0) {
                            if (line[4] == 0)
                                opponentScore += 30; //020010
                            else if (line[4] == t || line[4] == -1)
                                opponentScore += 5; //220010
                        } else if (line[9] == 3 - t) {
                            if (line[10] == 0)
                                opponentScore += 50 - 5; //200110
                            else
                                opponentScore += 50; //200112
                        } else if ((line[9] == t || line[9] == -1) && line[4] == 0)
                            opponentScore += 5; //020012
                    }
                } else if (line[7] == 3 - t) {
                    if (line[8] == 0) {
                        if (line[9] == 0) {
                            if (line[4] == 0)
                                opponentScore += 30; //020100
                            else if (line[4] == t || line[4] == -1)
                                opponentScore += 5; //220100
                        } else if (line[9] == 3 - t) {
                            if (line[10] == t || line[10] == -1)
                                opponentScore += 50; //201012
                            else if (line[10] == 0)
                                opponentScore += 50 - 5; //201010
                        } else if (line[9] == t || line[9] == -1) {
                            if (line[4] == 0) {
                                if (line[3] == 0)
                                    opponentScore += 30; //0020102
                                else if (line[3] == t || line[3] == -1)
                                    opponentScore += 5; //2020102
                            }
                        }
                    } else if (line[8] == 3 - t) {
                        if (line[9] == 0) {
                            if (line[10] == 0) {
                                if (line[4] == 0)
                                    opponentScore += 200 - 5; //0201100
                                else if (line[4] == t || line[4] == -1) {
                                    opponentScore += 50 - 5; //2201100
                                }
                            } else if (line[10] == t || line[10] == -1) {
                                if (line[4] == 0)
                                    opponentScore += 200; //0201102
                                else if (line[4] == t || line[4] == -1)
                                    opponentScore += 50; //2201102
                            }
                        } else if (line[9] == 3 - t) {
                            if (line[10] == t || line[10] == -1)
                                opponentScore += 300; //201112
                        } else if (line[9] == t || line[9] == -1) {
                            if (line[4] == 0)
                                opponentScore += 50; //020112
                        }
                    } else if (line[8] == t || line[8] == -1) {
                        if (line[4] == 0 && line[3] == 0)
                            opponentScore += 5; //002012
                    }
                }
            }
            break;
    }
    if (cntLeft == 1 && cntRight == 3) {
        if (line[9] == 0 && line[10] == 0)
            return opponentScore + 10000000 - 50; //1211100
        else
            return opponentScore + 10000000; //12111
    }
    if (cntLeft == 3 && cntRight == 1) {
        if (line[1] == 0 && line[0] == 0)
            return opponentScore + 10000000 - 50; //0011121
        else
            return opponentScore + 10000000; //11121
    }
    if (cntLeft == 2 && cntRight == 2) {
        if (line[2] == 0 && line[1] == 0 && line[0] == 0 && line[8] == 0 && line[9] == 0 && line[10] == 0)
            return opponentScore + 10000000 - 2 * 5; //00011211000
        else if ((line[2] == 0 && line[1] == 0 && line[0] == 0) || (line[8] == 0 && line[9] == 0 && line[10] == 0))
            return opponentScore + 10000000 - 5; //00011211|11211000
        else
            return opponentScore + 10000000; //11211
    }
    if (cntLeft == 1 && cntRight == 2) {
        if (line[3] == 0 && line[8] == 0) {
            if (line[9] == 0 && line[10] == 0)
                return opponentScore + 1000 - 5; //01211000
            else
                return opponentScore + 1000; //012110
        } else if (line[8] == 0) {
            if (line[9] == 0 && line[10] == 0)
                return opponentScore + 300 - 5; //21211000
            else
                return opponentScore + 300; //212110
        } else if (line[3] == 0)
            return opponentScore + 300; //012112
    }
    if (cntLeft == 2 && cntRight == 1) {
        if (line[7] == 0 && line[2] == 0) {
            if (line[1] == 0 && line[0] == 0)
                return opponentScore + 1000 - 5; //00011210
            else
                return opponentScore + 1000; //011210
        } else if (line[2] == 0) {
            if (line[1] == 0 && line[0] == 0)
                return opponentScore + 300 - 5; //00011212
            else
                return opponentScore + 300; //011212
        } else if (line[7] == 0)
            return opponentScore + 300; //211210
    }
    if (cntLeft == 0 && cntRight == 2 && line[4] == 0) {
        if (line[3] == 3 - t) {
            if (line[8] == 0 && line[9] == 0 && line[10] == 0)
                return opponentScore + 300 - 5; //10211000
            else
                return opponentScore + 300; //10211
        }
    }
    if (cntLeft == 2 && cntRight == 0 && line[6] == 0) {
        if (line[7] == 3 - t) {
            if (line[2] == 0 && line[1] == 0 && line[0] == 0)
                return opponentScore + 300 - 5; //00011201
            else
                return opponentScore + 300; //11201
        }
    }
    if (cntLeft == 1 && cntRight == 1) {
        if ((line[3] == t || line[3] == -1) && line[7] == 0 && line[8] == 0)
            return opponentScore + 50; //212100
        if ((line[7] == t || line[7] == -1) && line[3] == 0 && line[2] == 0)
            return opponentScore + 50; //001212
        if (line[3] == 0 && line[2] == 3 - t && line[7] == 0 && line[8] == 3 - t) {
            if (line[1] == 0 && line[0] == 0 && line[9] == 0 && line[10] == 0)
                return opponentScore + 2 * 300 - 2 * 5; //00101210100
            else if ((line[1] == 0 && line[0] == 0) || (line[9] == 0 && line[10] == 0))
                return opponentScore + 2 * 300 - 5; //001012101||101210100
            else
                return opponentScore + 2 * 300; //1012101
        }
        if (line[3] == 0 && line[2] == 3 - t) {
            if (line[1] == 0 && line[0] == 0)
                return opponentScore + 300 - 5; //0010121
            else
                return opponentScore + 300; //10121
        }
        if (line[7] == 0 && line[8] == 3 - t) {
            if (line[9] == 0 && line[10] == 0)
                return opponentScore + 300 - 5; //1210100
            else
                return opponentScore + 300; //12101
        }
        if (line[3] == 0 && line[7] == 0) {
            if ((line[2] == t || line[2] == -1) && (line[8] == t || line[8] == -1))
                return opponentScore + 50; //2012102
            else if (((line[2] == t || line[2] == -1) && line[8] == 0) || ((line[8] == t || line[8] == -1) && line[2] == 0) || (line[2] == 0 && line[8] == 0))
                return opponentScore + 200; //2012100|0012102|0012100
        }
    }
    if (cntLeft == 0 && cntRight == 1 && line[4] == 0) {
        if (line[3] == 0 && line[2] == 3 - t)
            return opponentScore + 50; //10021
        if (line[3] == 3 - t) {
            if (line[2] == 0 && line[7] == 0)
                return opponentScore + 200; //010210
            else if (line[2] == 3 - t)
                return opponentScore + 300; //11021
            else if (((line[2] == t || line[2] == -1) && line[7] == 0) || (line[2] == 0 && (line[7] == t || line[7] == -1)))
                return opponentScore + 50; //210210|010212
        }
    }
    if (cntLeft == 1 && cntRight == 0 && line[6] == 0) {
        if (line[7] == 0 && line[8] == 3 - t)
            return opponentScore + 50; //12001
        if (line[7] == 3 - t) {
            if (line[8] == 0 && line[3] == 0)
                return opponentScore + 200; //012010
            else if (line[8] == 3 - t)
                return opponentScore + 300; //12011
            else if (((line[8] == t || line[8] == -1) && line[3] == 0) || (line[8] == 0 && (line[3] == t || line[3] == -1)))
                return opponentScore + 50; //012012|212010
        }
    }
    if (cntLeft == 0 && cntRight == 0 && line[4] == 0 && line[6] == 0) {
        if (line[3] == 3 - t && line[7] == 3 - t)
            return opponentScore + 50; //10201
    }
    return opponentScore;
}