#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n) { for (int i = 0; i < n; ++i) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) { a = find(a); b = find(b); if (a == b) return false; p[a] = b; return true; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    if (!(cin >> N >> M)) return 0;
    vector<string> g(N);
    for (int i = 0; i < N; ++i) cin >> g[i];
    DSU dsu(N * M);
    int cow = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (g[i][j] == 'C') { ++cow; continue; }
            if (g[i][j] != 'G') continue;
            if (i + 1 < N && g[i + 1][j] == 'C') dsu.unite(i * M + j, (i + 1) * M + j);
            if (i - 1 >= 0 && g[i - 1][j] == 'C') dsu.unite(i * M + j, (i - 1) * M + j);
            if (j + 1 < M && g[i][j + 1] == 'C') dsu.unite(i * M + j, i * M + (j + 1));
            if (j - 1 >= 0 && g[i][j - 1] == 'C') dsu.unite(i * M + j, i * M + (j - 1));
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) if (g[i][j] == 'C') {
            if (dsu.find(i * M + j) == i * M + j) ++ans;
        }
    }
    cout << cow - ans << '\n';
    return 0;
}
