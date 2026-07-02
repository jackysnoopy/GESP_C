#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Edge {
    int to, rev;
    ll cap;
};

const int MAXN = 1000005;
vector<Edge> graph[MAXN];
int level[MAXN];
int iter[MAXN];

void addEdge(int from, int to, ll cap) {
    graph[from].push_back({to, (int)graph[to].size(), cap});
    graph[to].push_back({from, (int)graph[from].size() - 1, 0});
}

bool bfs(int s, int t, int n) {
    fill(level, level + n + 1, -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < (int)graph[v].size(); i++) {
            Edge& e = graph[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
    return level[t] >= 0;
}

ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < (int)graph[v].size(); i++) {
        Edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll maxFlow(int s, int t, int n) {
    ll flow = 0;
    while (bfs(s, t, n)) {
        fill(iter, iter + n + 1, 0);
        ll d;
        while ((d = dfs(s, t, (ll)1e18)) > 0) {
            flow += d;
        }
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    for (int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }

    cout << maxFlow(s, t, n) << "\n";
    return 0;
}
