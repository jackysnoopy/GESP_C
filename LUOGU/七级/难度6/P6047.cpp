#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
const int MAXN = 600005;
const int MAXM = 300005;
const ll INF = 1e18;

int n, m;
ll a[MAXN], b[MAXN];

struct Edge {
    int to, next;
    ll cap;
} edges[MAXM * 6];

int head[MAXN], edgeCnt;
int level[MAXN], cur[MAXN];

void addEdge(int u, int v, ll cap) {
    edges[edgeCnt] = {v, head[u], cap};
    head[u] = edgeCnt++;
    edges[edgeCnt] = {u, head[v], 0};
    head[v] = edgeCnt++;
}

bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    level[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (level[v] == -1 && edges[i].cap > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[t] != -1;
}

ll dfs(int u, int t, ll flow) {
    if (u == t) return flow;
    ll ret = 0;
    for (int& i = cur[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (level[v] == level[u] + 1 && edges[i].cap > 0) {
            ll f = dfs(v, t, min(flow - ret, edges[i].cap));
            edges[i].cap -= f;
            edges[i ^ 1].cap += f;
            ret += f;
            if (ret == flow) break;
        }
    }
    return ret;
}

ll maxFlow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) {
        memcpy(cur, head, sizeof(head));
        flow += dfs(s, t, INF);
    }
    return flow;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    edgeCnt = 0;
    
    int S = 0, T = 2 * n + 1;
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &b[i]);
    }
    
    for (int i = 1; i < n; i++) {
        addEdge(S, i, a[i]);
    }
    for (int j = 2; j <= n; j++) {
        addEdge(j + n, T, b[j]);
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u - 1, v + 1 + n, INF);
    }
    
    printf("%lld\n", maxFlow(S, T));
    
    return 0;
}
