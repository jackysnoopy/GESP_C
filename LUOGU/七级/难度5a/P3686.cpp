#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Edge {
    int to;
    ll cost;
    bool is_round;
};

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    
    vector<int> a(d);
    for (int i = 0; i < d; i++) {
        scanf("%d", &a[i]);
    }
    
    int m;
    scanf("%d", &m);
    
    // 使用Dijkstra算法
    vector<vector<Edge>> adj(n + 1);
    
    for (int i = 0; i < m; i++) {
        int s, di;
        char t;
        ll p;
        scanf("%d%d %c%lld", &s, &di, &t, &p);
        adj[s].push_back({di, p, t == 'R'});
    }
    
    // 计算每段路程的最小花费
    ll total = 0;
    for (int i = 0; i < d - 1; i++) {
        int from = a[i], to = a[i + 1];
        
        // Dijkstra
        vector<ll> dist(n + 1, INF);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        dist[from] = 0;
        pq.push({0, from});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& e : adj[u]) {
                if (dist[u] + e.cost < dist[e.to]) {
                    dist[e.to] = dist[u] + e.cost;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        
        total += dist[to];
    }
    
    printf("%lld\n", total);
    
    return 0;
}
