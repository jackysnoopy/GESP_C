#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) cin >> p[i];
        vector<bool> vis(n + 1, false);
        vector<int> cycles;
        for (int i = 1; i <= n; ++i) {
            if (vis[i]) continue;
            int cnt = 0, cur = i;
            while (!vis[cur]) { vis[cur] = true; cur = p[cur]; cnt++; }
            if (cnt > 1) cycles.push_back(cnt);
        }
        long long ans = 1;
        vector<long long> fact(n + 1, 1);
        for (int i = 2; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
        for (int c : cycles) ans = ans * fact[c] % MOD;
        cout << ans << '\n';
    }
    return 0;
}
