#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 1000005;
int n;
int a[MAXN];
int in_deg[MAXN];
bool vis[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++in_deg[a[i]];
    }
    queue<int> q;
    for (int i = 1; i <= n; ++i) if (in_deg[i] == 0) q.push(i);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = true;
        int v = a[u];
        if (vis[v]) continue;
        ++ans;
        vis[v] = true;
        int w = a[v];
        if (!vis[w] && --in_deg[w] == 0) q.push(w);
    }
    // 处理剩余环
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            int len = 0, x = i;
            while (!vis[x]) { vis[x] = true; ++len; x = a[x]; }
            ans += len - 1;
        }
    }
    cout << ans << "\n";
    return 0;
}
