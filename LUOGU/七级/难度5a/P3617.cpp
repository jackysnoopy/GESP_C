#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<pair<int, double>> adj[MAXN];
bool visited[MAXN];
double dist[MAXN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b, c == 0 ? 0 : 1.0});
        adj[b].push_back({a, c == 0 ? 0 : 1.0});
    }
    
    // 使用Dijkstra算法
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, 1});
    dist[1] = 0;
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (auto [v, w] : adj[u]) {
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    printf("%.3f\n", dist[n]);
    
    return 0;
}
