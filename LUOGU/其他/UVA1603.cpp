#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> matchsticks;
vector<vector<int>> squares;
vector<int> square_cnt;

bool dfs(int depth, int maxd) {
    bool all_destroyed = true;
    int max_cover = 0, max_idx = -1;
    for (int i = 0; i < (int)squares.size(); ++i) {
        if (square_cnt[i] <= 0) continue;
        all_destroyed = false;
        if ((int)squares[i].size() > max_cover) {
            max_cover = squares[i].size();
            max_idx = i;
        }
    }
    if (all_destroyed) return true;
    if (depth >= maxd) return false;
    int h = 0;
    for (int i = 0; i < (int)squares.size(); ++i)
        if (square_cnt[i] > 0) h++;
    if (depth + (h + max_cover - 1) / max_cover > maxd) return false;

    vector<int> saved = square_cnt;
    for (int ms : squares[max_idx]) {
        if (matchsticks[ms] == 0) continue;
        for (int j = 0; j < (int)squares.size(); ++j)
            for (int k = 0; k < (int)squares[j].size(); ++k)
                if (squares[j][k] == ms) square_cnt[j]--;
        matchsticks[ms] = 0;
        if (dfs(depth + 1, maxd)) return true;
        matchsticks[ms] = 1;
        for (int j = 0; j < (int)squares.size(); ++j) {
            square_cnt[j] = saved[j];
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        m = 2 * n * (n + 1);
        matchsticks.assign(m, 1);
        squares.clear();
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                for (int sz = 1; r + sz <= n && c + sz <= n; ++sz) {
                    vector<int> sq;
                    for (int i = 0; i < sz; ++i) {
                        sq.push_back((r * (2 * n + 1) + c + i));
                        sq.push_back((r * (2 * n + 1) + n + 1 + c + i));
                        sq.push_back((r + i) * (2 * n + 1) + c);
                        sq.push_back((r + i) * (2 * n + 1) + c + sz);
                    }
                    squares.push_back(sq);
                }
            }
        }
        int total_ms; cin >> total_ms;
        for (int i = 0; i < total_ms; ++i) {
            int x; cin >> x;
            matchsticks[x] = 0;
        }
        square_cnt.resize(squares.size());
        for (int i = 0; i < (int)squares.size(); ++i) {
            square_cnt[i] = 0;
            for (int ms : squares[i]) square_cnt[i] += matchsticks[ms];
        }
        for (int d = 0; d <= m; ++d) {
            if (dfs(0, d)) { cout << d << '\n'; break; }
        }
    }
    return 0;
}
