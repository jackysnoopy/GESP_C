#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int M[MAXN];
priority_queue<int> pq[MAXN];
int ans = 0;

void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
        if (pq[v].size() > pq[u].size()) swap(pq[u], pq[v]);
        while (!pq[v].empty()) {
            pq[u].push(pq[v].top());
            pq[v].pop();
        }
    }
    pq[u].push(M[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> M[i];
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        adj[f].push_back(i);
    }
    
    dfs(1);
    
    while (pq[1].size() > 1) {
        int a = pq[1].top(); pq[1].pop();
        int b = pq[1].top(); pq[1].pop();
        ans += max(a, b);
        pq[1].push(max(a, b));
    }
    
    cout << ans + pq[1].top() << "\n";
    return 0;
}
