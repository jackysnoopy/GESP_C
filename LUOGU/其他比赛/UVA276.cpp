#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;

int n, m;
int dist[MAXN][MAXN];
int parent[MAXN];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    while (cin >> n >> m && n) {
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 1; i <= n; i++) dist[i][i] = 0;
        
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = dist[v][u] = w;
        }
        
        floyd();
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                ans = max(ans, dist[i][j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
