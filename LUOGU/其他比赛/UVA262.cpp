#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Edge {
    int to, cap, flow, rev;
};

const int MAXN = 105;
vector<Edge> graph[MAXN];
int level[MAXN], iter[MAXN];

void addEdge(int from, int to, int cap) {
    graph[from].push_back({to, cap, 0, (int)graph[to].size()});
    graph[to].push_back({from, 0, 0, (int)graph[from].size() - 1});
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &e : graph[v]) {
            if (e.cap - e.flow > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] >= 0;
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < (int)graph[v].size(); i++) {
        Edge &e = graph[v][i];
        if (e.cap - e.flow > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap - e.flow));
            if (d > 0) {
                e.flow += d;
                graph[e.to][e.rev].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        memset(iter, 0, sizeof(iter));
        int d;
        while ((d = dfs(s, t, INT_MAX)) > 0) {
            flow += d;
        }
    }
    return flow;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i <= n; i++) graph[i].clear();

        int s, t;
        cin >> s >> t;

        for (int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            addEdge(u, v, c);
        }

        cout << maxFlow(s, t) << endl;
    }

    return 0;
}
