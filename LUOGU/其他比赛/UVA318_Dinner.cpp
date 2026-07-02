#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 505;
int n, m;
int a[MAXN], b[MAXN];
bool vis[MAXN];
int match[MAXN];
vector<int> adj[MAXN];

bool dfs(int u) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> b[i];
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i] + b[j] <= 1000) {
                    adj[i].push_back(j);
                }
            }
        }
        memset(match, -1, sizeof(match));
        int result = 0;
        for (int i = 1; i <= n; i++) {
            memset(vis, false, sizeof(vis));
            if (dfs(i)) result++;
        }
        cout << result << "\n";
    }
    return 0;
}
