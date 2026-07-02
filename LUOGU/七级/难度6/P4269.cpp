#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, B;
    cin >> N >> B;
    vector<int> f(N + 1);
    for (int i = 1; i <= N; i++) cin >> f[i];
    vector<int> s(B + 1), d(B + 1);
    for (int i = 1; i <= B; i++) cin >> s[i] >> d[i];
    vector<int> ans(B + 1);
    for (int i = 1; i <= B; i++) {
        vector<bool> vis(N + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        bool ok = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == N) { ok = true; break; }
            for (int v = u + 1; v <= min(N, u + d[i]); v++) {
                if (!vis[v] && f[v] <= s[i]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
            for (int v = u - 1; v >= max(1, u - d[i]); v--) {
                if (!vis[v] && f[v] <= s[i]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        ans[i] = ok ? 1 : 0;
    }
    for (int i = 1; i <= B; i++) cout << ans[i] << "\n";
    return 0;
}
