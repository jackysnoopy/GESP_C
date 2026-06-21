#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> a(n, vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) { int x; cin >> x; a[i][n] = x; }
        for (int i = 0; i < n; ++i) { int x; cin >> x; a[i][n] ^= x; a[i][i] = 1; }
        int u, v;
        while (cin >> u >> v && (u || v)) {
            a[u - 1][v - 1] = 1;
            a[v - 1][u - 1] = 1;
        }
        int rank = 0;
        for (int col = 0; col < n && rank < n; ++col) {
            int mx = rank;
            for (int r = rank + 1; r < n; ++r)
                if (a[r][col]) { mx = r; break; }
            if (!a[mx][col]) continue;
            swap(a[rank], a[mx]);
            for (int r = 0; r < n; ++r) {
                if (r == rank || !a[r][col]) continue;
                for (int c = col; c <= n; ++c) a[r][c] ^= a[rank][c];
            }
            rank++;
        }
        bool impossible = false;
        for (int r = rank; r < n; ++r)
            if (a[r][n]) { impossible = true; break; }
        if (impossible) cout << "Oh,it's impossible~!!" << '\n';
        else cout << (1LL << (n - rank)) << '\n';
    }
    return 0;
}
