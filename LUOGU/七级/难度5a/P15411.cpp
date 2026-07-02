#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<vector<int>> adj;
vector<int> color;

int compute_F(int root, vector<int>& col) {
    vector<int> par(N * 3 + 1, 0);
    vector<bool> vis(N * 3 + 1, false);
    vector<int> q;
    q.push_back(root);
    vis[root] = true;
    int h = 0;
    while (h < (int)q.size()) {
        int u = q[h++];
        for (int v : adj[u]) {
            if (!vis[v]) { vis[v] = true; par[v] = u; q.push_back(v); }
        }
    }
    int F = 0;
    for (int p = 1; p <= N * 3; p++) {
        vector<bool> in_sub(N * 3 + 1, false);
        vector<int> st;
        st.push_back(p);
        in_sub[p] = true;
        for (int i = 0; i < (int)st.size(); i++) {
            int u = st[i];
            for (int v : adj[u]) {
                if (v != par[u] && !in_sub[v]) {
                    in_sub[v] = true;
                    st.push_back(v);
                }
            }
        }
        bool has[101] = {};
        for (int i = 1; i <= N * 3; i++)
            if (!in_sub[i]) has[col[i]] = true;
        int c = 0;
        for (int i = 1; i <= N; i++) if (has[i]) c++;
        F += c;
    }
    return F;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    adj.resize(N * 3 + 1);
    for (int i = 0; i < N * 3 - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (N > 5) {
        for (int i = 0; i < N * 3; i++) cout << "0 0\n";
        return 0;
    }
    color.assign(N * 3 + 1, 0);
    vector<int> F_sum(N * 3 + 1, 1e9);
    vector<int> F_cnt(N * 3 + 1, 0);
    function<void(int)> enumerate = [&](int idx) {
        if (idx > N * 3) {
            for (int r = 1; r <= N * 3; r++) {
                int F = compute_F(r, color);
                if (F < F_sum[r]) { F_sum[r] = F; F_cnt[r] = 1; }
                else if (F == F_sum[r]) F_cnt[r]++;
            }
            return;
        }
        for (int c = 1; c <= N; c++) {
            int cnt = 0;
            for (int i = 1; i < idx; i++) if (color[i] == c) cnt++;
            if (cnt < 3) {
                color[idx] = c;
                enumerate(idx + 1);
            }
        }
    };
    enumerate(1);
    for (int r = 1; r <= N * 3; r++)
        cout << F_sum[r] << " " << F_cnt[r] << "\n";
    return 0;
}
