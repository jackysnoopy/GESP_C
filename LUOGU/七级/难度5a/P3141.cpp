#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

int parent[500005];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int A, B, n, m;
    cin >> A >> B >> n >> m;
    
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    
    // Sort fence positions
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    // Create edges for vertical fences
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        int cost = (i == 0) ? a[0] : a[i] - a[i-1];
        edges.push_back({i, i + 1, cost});
    }
    edges.push_back({n, n + 1, A - a[n-1]});
    
    // Create edges for horizontal fences
    for (int i = 0; i < m; i++) {
        int cost = (i == 0) ? b[0] : b[i] - b[i-1];
        edges.push_back({n + 1 + i, n + 1 + i + 1, cost});
    }
    edges.push_back({n + m + 1, n + m + 2, B - b[m-1]});
    
    // Kruskal's algorithm
    for (int i = 0; i <= n + m + 2; i++) {
        parent[i] = i;
    }
    
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    
    long long total = 0;
    for (const Edge& e : edges) {
        if (unite(e.u, e.v)) {
            total += e.w;
        }
    }
    
    cout << total << "\n";
    return 0;
}
