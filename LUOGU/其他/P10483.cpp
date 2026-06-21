#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, W;
vector<int> c;
int ans;

void dfs(int idx, int used, vector<int>& loads) {
    if (used >= ans) return;
    if (idx == n) { ans = used; return; }
    for (int i = 0; i < used; ++i) {
        if (loads[i] + c[idx] <= W) {
            loads[i] += c[idx];
            dfs(idx + 1, used, loads);
            loads[i] -= c[idx];
        }
    }
    if (used < ans) {
        loads[used] = c[idx];
        dfs(idx + 1, used + 1, loads);
        loads[used] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> W)) return 0;
    c.resize(n);
    for (int i = 0; i < n; ++i) cin >> c[i];
    sort(c.begin(), c.end(), greater<int>());
    ans = n;
    vector<int> loads(n, 0);
    dfs(0, 0, loads);
    cout << ans << '\n';
    return 0;
}
