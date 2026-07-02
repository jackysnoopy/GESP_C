#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAXN = 5005;
const long long INF = 1e18;

int n, m;
long long k;
vector<pair<int,int>> adj[MAXN];
long long dist[MAXN];
int prev_node[MAXN];
bool on_path[MAXN];

void dijkstra(int src) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        prev_node[i] = -1;
    }
    dist[src] = 0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        pair<long long,int> top = pq.top();
        pq.pop();
        long long d = top.first;
        int u = top.second;
        if (d > dist[u]) continue;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev_node[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void mark_path(int t) {
    int u = t;
    while (u != -1) {
        on_path[u] = true;
        u = prev_node[u];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back({b, 1});
        adj[b].push_back({a, 1});
    }

    int s1, t1, s2, t2;
    cin >> s1 >> t1 >> s2 >> t2;

    // Find shortest path for Du (s1 -> t1)
    dijkstra(s1);
    if (dist[t1] == INF) {
        cout << fixed << setprecision(12) << 0.0 << "\n";
        return 0;
    }
    vector<int> path1;
    for (int u = t1; u != -1; u = prev_node[u]) {
        path1.push_back(u);
    }
    reverse(path1.begin(), path1.end());

    // Find shortest path for Wo (s2 -> t2)
    dijkstra(s2);
    if (dist[t2] == INF) {
        cout << fixed << setprecision(12) << 0.0 << "\n";
        return 0;
    }
    vector<int> path2;
    for (int u = t2; u != -1; u = prev_node[u]) {
        path2.push_back(u);
    }
    reverse(path2.begin(), path2.end());

    // Collect edges on paths and count usage
    // Each edge is represented by (min(u,v), max(u,v))
    vector<pair<int,int>> edges_on_path;
    vector<int> usage;

    // Mark edges on path1
    for (int i = 0; i + 1 < (int)path1.size(); i++) {
        int u = path1[i], v = path1[i+1];
        if (u > v) swap(u, v);
        edges_on_path.push_back({u, v});
        usage.push_back(1);
    }

    // Mark edges on path2, check for overlap
    for (int i = 0; i + 1 < (int)path2.size(); i++) {
        int u = path2[i], v = path2[i+1];
        if (u > v) swap(u, v);
        bool found = false;
        for (int j = 0; j < (int)edges_on_path.size(); j++) {
            if (edges_on_path[j] == make_pair(u, v)) {
                usage[j]++;
                found = true;
                break;
            }
        }
        if (!found) {
            edges_on_path.push_back({u, v});
            usage.push_back(1);
        }
    }

    // Greedy allocation: upgrade edge with highest marginal benefit
    // Each edge starts at speed 1, marginal benefit of x-th upgrade: 1/(x*(x+1))
    int E = edges_on_path.size();
    vector<int> upgrades(E, 0);

    // Use priority queue: (marginal benefit, edge index)
    priority_queue<pair<double, int>> pq;
    for (int i = 0; i < E; i++) {
        pq.push({1.0 / (1.0 * 2.0), i}); // first upgrade benefit: 1/2
    }

    long long remaining = k;
    while (remaining > 0 && !pq.empty()) {
        pair<double, int> top = pq.top();
        pq.pop();
        double benefit = top.first;
        int idx = top.second;
        if (benefit < 1e-15) break;
        upgrades[idx]++;
        remaining--;
        double new_speed = 1.0 + upgrades[idx];
        double next_benefit = 1.0 / (new_speed * (new_speed + 1.0));
        pq.push({next_benefit, idx});
    }

    // Calculate total time
    double total_time = 0;
    for (int i = 0; i < E; i++) {
        double speed = 1.0 + upgrades[i];
        total_time += usage[i] / speed;
    }

    cout << fixed << setprecision(12) << total_time << "\n";

    return 0;
}
