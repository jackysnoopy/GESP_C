#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

const int INF = 1e9;

struct Dinic {
    struct Edge { int to, rev, cap; };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;
    Dinic(int n): g(n), level(n), iter(n), n(n) {}
    void addEdge(int from, int to, int cap) {
        g[from].push_back({to, (int)g[to].size(), cap});
        g[to].push_back({from, (int)g[from].size() - 1, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s] = 0; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1; q.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) { e.cap -= d; g[e.to][e.rev].cap += d; return d; }
            }
        }
        return 0;
    }
    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, B;
    cin >> N >> B;
    // rankOf[i][b] = cow i 对牛棚 b 的偏好排名 (1..B)
    vector<vector<int>> rankOf(N + 1, vector<int>(B + 1));
    for (int i = 1; i <= N; i++) {
        for (int r = 1; r <= B; r++) {
            int b; cin >> b;
            rankOf[i][b] = r;
        }
    }
    vector<int> cap(B + 1);
    for (int b = 1; b <= B; b++) cin >> cap[b];

    int S = 0, T = N + B + 1, nodes = N + B + 2;
    // 判定排名窗口 [lo, hi] 是否能完成分配
    auto feasible = [&](int lo, int hi) -> bool {
        Dinic din(nodes);
        for (int i = 1; i <= N; i++) din.addEdge(S, i, 1);
        for (int i = 1; i <= N; i++)
            for (int b = 1; b <= B; b++)
                if (rankOf[i][b] >= lo && rankOf[i][b] <= hi)
                    din.addEdge(i, N + b, 1);
        for (int b = 1; b <= B; b++) din.addEdge(N + b, T, cap[b]);
        return din.maxflow(S, T) == N;
    };

    // 滑动窗口：hi(lo) 随 lo 单调不减
    int ans = B, hi = 1;
    for (int lo = 1; lo <= B; lo++) {
        if (hi < lo) hi = lo;
        while (hi <= B && !feasible(lo, hi)) hi++;
        if (hi <= B) ans = min(ans, hi - lo + 1);
    }
    cout << ans << "\n";
    return 0;
}
