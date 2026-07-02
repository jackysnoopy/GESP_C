#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100005;
vector<int> adj[MAXN];
int need[MAXN], cover[MAXN];
int n, s, k;
int ans = 0;
void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        need[u] = max(need[u], need[v] - 1);
    }
    if (need[u] == k) {
        ans++;
        need[u] = -s;
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> s >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) need[i] = 0;
    dfs(1, 0);
    if (need[1] > 0) ans++;
    cout << ans << endl;
    return 0;
}