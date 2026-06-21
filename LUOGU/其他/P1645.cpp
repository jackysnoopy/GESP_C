#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<tuple<int,int,int>> con;
    int maxR = 0;
    for (int i = 0; i < n; i++) {
        int l, r, c; cin >> l >> r >> c;
        con.push_back(make_tuple(l, r, c));
        if (r > maxR) maxR = r;
    }
    int V = maxR + 1;
    vector<int> dist(V + 1, 0);
    vector<tuple<int,int,int>> edges;
    for (int ii = 0; ii < (int)con.size(); ii++) {
        edges.push_back(make_tuple(get<0>(con[ii]) - 1, get<1>(con[ii]), get<2>(con[ii])));
    }
    for (int i = 1; i <= maxR; i++) {
        edges.push_back(make_tuple(i - 1, i, 1));
        edges.push_back(make_tuple(i, i - 1, 0));
    }
    for (int iter = 0; iter < V; iter++) {
        bool updated = false;
        for (int ii = 0; ii < (int)edges.size(); ii++) {
            int u = get<0>(edges[ii]), v = get<1>(edges[ii]), w = get<2>(edges[ii]);
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) break;
    }
    cout << dist[maxR] << "\n";
    return 0;
}
