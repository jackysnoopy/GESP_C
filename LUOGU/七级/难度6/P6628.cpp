#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2505;
vector<int> adj[MAXN];
int dist[MAXN][MAXN];
bool must[MAXN][MAXN];

void bfs(int s, int n) {
    vector<int> q;
    q.push_back(s);
    dist[s][s] = 0;
    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        for (int v : adj[u]) {
            if (dist[s][v] == -1) {
                dist[s][v] = dist[s][u] + 1;
                q.push_back(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, s;
    cin >> n >> m >> s;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dist[i][j] = -1;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        must[u][v] = must[v][u] = true;
    }
    
    for (int i = 1; i <= n; i++) bfs(i, n);
    
    for (int i = 1; i <= n; i++) {
        if (i == s) cout << "0";
        else cout << " " << dist[s][i];
    }
    cout << "\n";
    
    return 0;
}
