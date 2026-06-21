#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 20005;
int par[MAXN], enemy[MAXN];

int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }

void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x != y) par[x] = y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int,pair<int,int>>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
    }
    sort(edges.begin(), edges.end(), greater<pair<int,pair<int,int>>>());
    
    for (int i = 1; i <= n; i++) { par[i] = i; enemy[i] = 0; }
    
    for (auto& e : edges) {
        int a = e.second.first, b = e.second.second, w = e.first;
        int ra = find(a), rb = find(b);
        if (ra == rb) { cout << w << "\n"; return 0; }
        if (enemy[ra]) unite(enemy[ra], rb);
        else enemy[ra] = rb;
        if (enemy[rb]) unite(enemy[rb], ra);
        else enemy[rb] = ra;
    }
    cout << 0 << "\n";
    return 0;
}
