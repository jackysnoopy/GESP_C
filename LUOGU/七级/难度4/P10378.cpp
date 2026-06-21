#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> color(n + 1, -1);
    int minB = 0, maxB = 0;
    for (int start = 1; start <= n; start++) {
        if (color[start] != -1) continue;
        // BFS bipartite coloring
        int cnt[2] = {0, 0};
        vector<int> q;
        q.push_back(start);
        color[start] = 0;
        cnt[0]++;
        for (int i = 0; i < (int)q.size(); i++) {
            int u = q[i];
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    cnt[color[v]]++;
                    q.push_back(v);
                }
            }
        }
        minB += min(cnt[0], cnt[1]);
        maxB += max(cnt[0], cnt[1]);
    }
    cout << minB << " " << maxB << "\n";
    return 0;
}
