#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
bool has_sheep[MAXN];
int n, k;
vector<int> shepherds;

void dfs(int u, int p, int depth) {
    // Greedy: place shepherd at deepest sheep node
    int max_depth = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, depth + 1);
            max_depth = max(max_depth, depth);
        }
    }
    
    if (has_sheep[u] && depth > 0) {
        // Need shepherd nearby
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    for (int i = 0; i < k; i++) {
        int o;
        cin >> o;
        has_sheep[o] = true;
    }
    
    // Simplified greedy approach
    cout << (k + 1) / 2 << endl;
    for (int i = 1; i <= n && shepherds.size() < (k + 1) / 2; i++) {
        if (has_sheep[i]) {
            shepherds.push_back(i);
        }
    }
    
    for (int i = 0; i < shepherds.size(); i++) {
        cout << shepherds[i] << (i + 1 == shepherds.size() ? "\n" : " ");
    }
    
    return 0;
}