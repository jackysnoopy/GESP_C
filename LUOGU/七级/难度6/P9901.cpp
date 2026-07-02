#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1e6 + 5;
const long long INF = 1e18;

struct Edge {
    int to, rev;
    long long cap;
};

vector<Edge> adj[MAXN];
int level[MAXN], iter[MAXN];

void add_edge(int from, int to, long long cap) {
    adj[from].push_back({to, (int)adj[to].size(), cap});
    adj[to].push_back({from, (int)adj[from].size() - 1, 0});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto& e : adj[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

long long dfs(int v, int t, long long f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < adj[v].size(); i++) {
        Edge& e = adj[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            long long d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                adj[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

long long max_flow(int s, int t) {
    long long flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        long long d;
        while ((d = dfs(s, t, INF)) > 0) {
            flow += d;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }
    
    cout << max_flow(s, t) << "\n";
    return 0;
}