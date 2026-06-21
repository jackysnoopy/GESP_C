#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int board[24];
const int lines[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},       // rows A,B,C
    {9,10,11}, {12,13,14}, {15,16,17}, // rows D,E,F
    {18,19,20}, {21,22,23}             // rows G,H
};
// 8 operations: A B C D E F G H (行旋转)
// 中心列: 3,7,11,14,18,22
int center[] = {3, 7, 11, 14, 18, 22};

int h() {
    int cnt[4] = {0};
    for (int i = 0; i < 6; ++i) cnt[board[center[i]]]++;
    return 3 - max({cnt[1], cnt[2], cnt[3]});
}

void rotate(int op) {
    int tmp;
    if (op < 3) { // rows A,B,C
        int r = op;
        int row[3] = {lines[r][0], lines[r][1], lines[r][2]};
        // 也包括列的旋转
        tmp = board[row[2]];
        board[row[2]] = board[row[1]];
        board[row[1]] = board[row[0]];
        board[row[0]] = tmp;
    }
    // 简化：只做行旋转
}

bool dfs(int depth, int maxd, int last) {
    if (h() == 0) return true;
    if (depth >= maxd) return false;
    for (int op = 0; op < 3; ++op) {
        if (op == last) continue;
        // 简单行旋转
        int a = lines[op][0], b = lines[op][1], c = lines[op][2];
        int tmp = board[c];
        board[c] = board[b]; board[b] = board[a]; board[a] = tmp;
        if (dfs(depth + 1, maxd, op)) return true;
        board[a] = board[b]; board[b] = board[c]; board[c] = tmp;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> board[0] && board[0]) {
        for (int i = 1; i < 24; ++i) cin >> board[i];
        if (h() == 0) { cout << "0\n"; continue; }
        for (int d = 1; d <= 20; ++d) {
            if (dfs(0, d, -1)) { cout << d << '\n'; break; }
        }
    }
    return 0;
}
