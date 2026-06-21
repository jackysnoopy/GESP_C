#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Solver {
    vector<string> board;
    int rows[9], cols[9], boxes[9];

    void init() {
        for (int i = 0; i < 9; ++i) rows[i] = cols[i] = boxes[i] = 0;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                if (board[i][j] != '0') {
                    int d = board[i][j] - '1';
                    rows[i] |= 1 << d;
                    cols[j] |= 1 << d;
                    boxes[(i/3)*3 + j/3] |= 1 << d;
                }
    }

    bool solve(int pos) {
        if (pos == 81) return true;
        int r = pos / 9, c = pos % 9;
        if (board[r][c] != '0') return solve(pos + 1);
        int b = (r/3)*3 + c/3;
        int used = rows[r] | cols[c] | boxes[b];
        for (int d = 0; d < 9; ++d) {
            if (used & (1 << d)) continue;
            board[r][c] = char('1' + d);
            rows[r] |= 1 << d;
            cols[c] |= 1 << d;
            boxes[b] |= 1 << d;
            if (solve(pos + 1)) return true;
            rows[r] ^= 1 << d;
            cols[c] ^= 1 << d;
            boxes[b] ^= 1 << d;
        }
        board[r][c] = '0';
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        Solver solver;
        solver.board.resize(9);
        for (int i = 0; i < 9; ++i) cin >> solver.board[i];
        solver.init();
        solver.solve(0);
        for (int i = 0; i < 9; ++i) cout << solver.board[i] << '\n';
    }
    return 0;
}
