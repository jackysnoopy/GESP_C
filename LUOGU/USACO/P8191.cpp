#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 1) { for (int i = 0; i < n; i++) p[i] = i; }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) swap(x, y);
        p[y] = x;
        if (r[x] == r[y]) r[x]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    
    // Edge weight: (x_i - x_j)^2 + (y_i - y_j)^2
    // y is in [0, 10], x is in [0, 10^6]
    // For each y value (0..10), maintain the closest point seen so far.
    // When processing point i, for each y value, the closest point with that y
    // gives a candidate edge.
    
    // Sort by x coordinate
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) { return x[i] < x[j]; });
    
    struct Edge { long long w; int u, v; };
    vector<Edge> edges;
    
    // For each y value, track the last point with that y
    vector<int> last(11, -1);
    
    for (int k = 0; k < n; k++) {
        int i = idx[k];
        // Connect to nearest point in each y value
        for (int yy = 0; yy <= 10; yy++) {
            if (last[yy] >= 0) {
                int j = last[yy];
                long long w = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                edges.push_back({w, i, j});
            }
        }
        last[y[i]] = i;
    }
    
    // Also connect to nearest point in each y value from the right
    fill(last.begin(), last.end(), -1);
    for (int k = n - 1; k >= 0; k--) {
        int i = idx[k];
        for (int yy = 0; yy <= 10; yy++) {
            if (last[yy] >= 0) {
                int j = last[yy];
                long long w = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
                edges.push_back({w, i, j});
            }
        }
        last[y[i]] = i;
    }
    
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    
    DSU dsu(n);
    long long total = 0;
    int count = 0;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            count++;
            if (count == n - 1) break;
        }
    }
    
    cout << total << "\n";
    return 0;
}
