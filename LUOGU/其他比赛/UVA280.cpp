#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 105;
vector<int> adj[MAXN];
bool visited[MAXN];
int n;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        
        int u, v;
        while (cin >> u && u) {
            while (cin >> v && v) {
                adj[u].push_back(v);
            }
        }
        
        int q;
        cin >> q;
        while (q--) {
            int start;
            cin >> start;
            memset(visited, false, sizeof(visited));
            dfs(start);
            int count = 0;
            for (int i = 1; i <= n; i++) {
                if (!visited[i]) count++;
            }
            cout << count;
            for (int i = 1; i <= n; i++) {
                if (!visited[i]) cout << " " << i;
            }
            cout << endl;
        }
    }
    return 0;
}
