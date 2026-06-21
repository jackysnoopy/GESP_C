#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Solver {
    string flat;
    int rows[9], cols[9], boxes[9];

    void init() {
        for (int i = 0; i < 9; ++i) rows[i] = cols[i] = boxes[i] = 0;
        for (int i = 0; i < 81; ++i) {
            if (flat[i] == '.') continue;
            int d = flat[i] - '1';
            int r = i / 9, c = i % 9;
            rows[r] |= 1 << d;
            cols[c] |= 1 << d;
            boxes[(r/3)*3 + c/3] |= 1 << d;
        }
    }

    bool solve(int pos) {
        if (pos == 81) return true;
        if (flat[pos] != '.') return solve(pos + 1);
        int r = pos / 9, c = pos % 9;
        int b = (r/3)*3 + c/3;
        int used = rows[r] | cols[c] | boxes[b];
        for (int d = 0; d < 9; ++d) {
            if (used & (1 << d)) continue;
            flat[pos] = char('1' + d);
            rows[r] |= 1 << d;
            cols[c] |= 1 << d;
            boxes[b] |= 1 << d;
            if (solve(pos + 1)) return true;
            rows[r] ^= 1 << d;
            cols[c] ^= 1 << d;
            boxes[b] ^= 1 << d;
        }
        flat[pos] = '.';
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (cin >> line) {
        if (line == "end") break;
        Solver solver;
        solver.flat = line;
        solver.init();
        solver.solve(0);
        cout << solver.flat << '\n';
    }
    return 0;
}
