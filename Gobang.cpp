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
    alphaBeta((turn == 1 ? 6 : 7), INT_MIN, INT_MAX, &pos);
    return pos;
}

int Gobang::evaluate() {
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

int Gobang::alphaBeta(int depth, int alpha, int beta, pair<int, int> *pos) {
    if (judge() || !depth || !getTurn())
        return evaluate();
    int score;
    vector<pair<int, pair<int, int> > > candidates;
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 15; ++j) {
            if (!board[i][j] && isValid[i][j]) {
                drop({i, j});
                candidates.push_back({evaluate() + (board[i][j] == 1 ? -1 : 1) * (int) sqrt((i - 8) * (i - 8) + (j - 8) * (j - 8)), {i, j}});
                undo();
            }
        }
    }
    if (turn == 1) {
        score = INT_MIN;
        sort(candidates.begin(), candidates.end(), [](const auto &a, const auto &b) {
            return a.first > b.first;
        });
        for (int i = 0; i < candidates.size() && i < 5; ++i) {
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
        sort(candidates.begin(), candidates.end(), [](const auto &a, const auto &b) {
            return a.first < b.first;
        });
        for (int i = 0; i < candidates.size() && i < 5; ++i) {
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
