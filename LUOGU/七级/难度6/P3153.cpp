#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const int INF = 1e9;

struct Edge {
    int to, cap, rev;
};

vector<Edge> graph[MAXN];
int level[MAXN], iter[MAXN];

void addEdge(int from, int to, int cap) {
    graph[from].push_back({to, cap, (int)graph[to].size()});
    graph[to].push_back({from, 0, (int)graph[from].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto& e : graph[v]) {
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < (int)graph[v].size(); i++) {
        Edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}

int n, k;
char likes[55][55];

void buildGraph(int m) {
    for (int i = 0; i < MAXN; i++) graph[i].clear();
    int S = 0, T = 4 * n + 1;
    for (int i = 1; i <= n; i++) {
        addEdge(S, i, m);
        addEdge(i, i + n, k);
        addEdge(i + 2 * n, i + 3 * n, k);
        addEdge(i + 3 * n, T, m);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (likes[i][j] == 'Y') {
                addEdge(i, j + 3 * n, 1);
            } else {
                addEdge(i + n, j + 3 * n, 1);
                addEdge(i, j + 2 * n, 1);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> (likes[i] + 1);
    }
    int lo = 0, hi = n, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        buildGraph(mid);
        int flow = maxFlow(0, 4 * n + 1);
        if (flow == n * mid) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}
