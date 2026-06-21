#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 4002;
const long long INF = 1e18;
struct Edge { int to, rev; long long cap, cost; };
vector<Edge> graph[MAXN];
int par[MAXN], parEdge[MAXN];
long long dist[MAXN];
bool inq[MAXN];
void addEdge(int from, int to, long long cap, long long cost) {
    graph[from].push_back({to, (int)graph[to].size(), cap, cost});
    graph[to].push_back({from, (int)graph[from].size() - 1, 0, -cost});
}
pair<long long, long long> minCostFlow(int s, int t, int maxf) {
    long long flow = 0, cost = 0;
    while (flow < maxf) {
        memset(dist, 0x3f, sizeof(dist));
        memset(inq, false, sizeof(inq));
        dist[s] = 0;
        queue<int> q;
        q.push(s); inq[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop(); inq[u] = false;
            for (int i = 0; i < (int)graph[u].size(); i++) {
                Edge& e = graph[u][i];
                if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    par[e.to] = u; parEdge[e.to] = i;
                    if (!inq[e.to]) { q.push(e.to); inq[e.to] = true; }
                }
            }
        }
        if (dist[t] >= INF) break;
        long long f = maxf - flow;
        int v = t;
        while (v != s) {
            f = min(f, graph[par[v]][parEdge[v]].cap);
            v = par[v];
        }
        flow += f;
        cost += f * dist[t];
        v = t;
        while (v != s) {
            Edge& e = graph[par[v]][parEdge[v]];
            e.cap -= f;
            graph[v][e.rev].cap += f;
            v = par[v];
        }
    }
    return {flow, cost};
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    int r[1001];
    for (int i = 1; i <= N; i++) cin >> r[i];
    int p, m, f, n, s;
    cin >> p >> m >> f >> n >> s;
    // Node 0: source, 1..N: day usage, N+1..2N: day supply, 2N+1: sink
    int S = 0, T = 2 * N + 1;
    for (int i = 1; i <= N; i++) {
        addEdge(S, i, r[i], 0);           // day i needs r[i] napkins
        addEdge(N + i, T, r[i], 0);       // day i supply
    }
    for (int i = 1; i <= N; i++) {
        addEdge(S, N + i, INF, p);         // buy new napkins
        if (i + 1 <= N) addEdge(N + i, N + i + 1, INF, 0); // carry over
        if (i + m <= N) addEdge(N + i, i + m, INF, f);      // fast wash
        if (i + n <= N) addEdge(N + i, i + n, INF, s);      // slow wash
    }
    auto res = minCostFlow(S, T, N);
    cout << res.second << "\n";
    return 0;
}
