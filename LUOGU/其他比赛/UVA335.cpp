#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INF = 1e9;
int adj[105][105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int cas = 0;
    while (cin >> n >> m && (n || m)) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i == j) ? 0 : INF;

        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            adj[u][v] = adj[v][u] = w;
        }

        // Floyd-Warshall
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (adj[i][k] < INF && adj[k][j] < INF)
                        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

        cout << "Network " << ++cas << "\n";
        int q; cin >> q;
        while (q--) {
            int s, t; cin >> s >> t;
            s--; t--;
            if (adj[s][t] < INF)
                cout << "Minimum cost: " << adj[s][t] << "\n";
            else
                cout << "Impossible\n";
        }
        cout << "\n";
    }
    return 0;
}
