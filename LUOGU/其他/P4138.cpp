#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
vector<int> adj[100001];
int dfn[100001], low[100001], cnt, scnt;
int bel[100001];
stack<int> st;
bool inStack[100001];
int sz[100001];
void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    st.push(u); inStack[u] = true;
    for (int v : adj[u]) {
        if (!dfn[v]) { tarjan(v); low[u] = min(low[u], low[v]); }
        else if (inStack[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        scnt++;
        while (true) {
            int v = st.top(); st.pop();
            inStack[v] = false;
            bel[v] = scnt;
            sz[scnt]++;
            if (v == u) break;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    int ans = 0;
    for (int i = 1; i <= scnt; i++)
        if (sz[i] > 1) ans++;
    cout << ans << "\n";
    return 0;
}
